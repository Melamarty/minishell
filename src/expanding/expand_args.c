/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   expand_args.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mozennou <mozennou@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/01/09 16:21:19 by mozennou		  #+#	#+#			 */
/*   Updated: 2024/01/09 16:22:52 by mozennou		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"

void	norm_helper(t_list **res, int *l, char *string, t_list *args)
{
	t_list	*tmp;

	ft_lstadd_back(res, ft_lstnew(string, args->type));
	*l = 1;
	tmp = ft_lstlast(*res);
	tmp->expand = args->expand;
	tmp->type = args->type;
	tmp->fd = args->fd;
}

t_list	*ft_lstsplit(char *string, t_list **res, t_list *args)
{
	char	*str;
	t_list	*tmp;
	char	**split;
	int		i;

	i = 0;
	split = my_split(string);
	while (split[i])
	{
		str = ft_strdup(split[i]);
		ft_lstadd_back(res, ft_lstnew(str, 0));
		tmp = ft_lstlast(*res);
		tmp->expand = args->expand;
		tmp->type = args->type;
		tmp->fd = args->fd;
		i++;
	}
	return (*res);
}

static void	func(t_list *args, t_list **res, char *string, int *l)
{
	t_list	*tmp;

	if (args->pos && *l && ft_strlen(string))
	{
		tmp = ft_lstlast(*res);
		tmp->token = ft_strjoin(tmp->token, string);
		if (args->pos == 2)
			*l = 0;
	}
	else
	{
		if (args->expand)
			add_cpy(res, args, args->type, string);
		else
			ft_lstsplit(string, res, args);
	}
}

t_list	*expand_args(t_list *args, t_env *env, int m)
{
	t_list	*res;
	char	*string;
	int		l;

	res = NULL;
	l = 0;
	while (args)
	{
		if (args->expand != 1)
			string = ft_expand(args->token, env);
		else
			string = ft_strdup(args->token);
		if (args->pos == 1 && !l && ft_strlen(string))
			norm_helper(&res, &l, string, args);
		else
			func(args, &res, string, &l);
		args = args->next;
	}
	if (!m)
		return (wildcard(res));
	return (res);
}

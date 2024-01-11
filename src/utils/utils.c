/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mel-amar <mel-amar@student.1337.ma>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/01/07 17:47:34 by mel-amar		  #+#	#+#			 */
/*   Updated: 2024/01/11 12:02:48 by mel-amar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while ((str1[i] || str2[i]))
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		my_malloc(0, 1);
		exit(1);
	}
}

void	init_env (t_env *env)
{
	t_list	*tmp;
	char	*path;

	tmp = my_malloc(sizeof(t_list), 0);
	tmp->token = ft_strdup("OLDPWD");
	tmp->next = NULL;
	unset (&env, tmp);
	export_add_back(&env->ex_env, tmp->token);
	tmp->token = ft_strdup("_");
	unset (&env, tmp);
	tmp->token = ft_strdup ("_");
	unset (&env, tmp);
	env_add_back(&env->env, ft_strdup("_"), ft_strdup("./minishell"));
	tmp->token = ft_strdup("PWD");
	path = getcwd(NULL, 0);
	unset (&env, tmp);
	env_add_back(&env->env, ft_strdup("PWD"), path);
	free (path);
}


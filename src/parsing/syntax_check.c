/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:44:22 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 15:12:10 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	my_close(t_list *cpy)
{
	if (cpy->fd > 2)
		close(cpy->fd);
	cpy->fd = -1;
	return (0);
}

static int	func2(t_list *tk, t_list **p, t_list **pp)
{
	ft_lstadd_back(p, ft_lstnew(ft_strdup(tk->token), tk->type));
	(*pp) = ft_lstlast(*p);
	(*pp)->expand = tk->expand;
	(*pp)->pos = tk->pos;
	return (0);
}

static char	*chck(t_list *tk, char *str)
{
	if (str[ft_strlen(str) - 1] == '$' && !tk->expand
		&& tk->next && (tk->next->type == TOKEN_D_Q
			|| tk->next->type == TOKEN_S_Q))
	{
		if (ft_strlen(str) == 1)
			return (ft_strdup(""));
		else
			return (ft_substr(str, 0, ft_strlen(str) - 1));
	}
	return (str);
}

t_list	*out_of_quotes(t_list	*tk, t_env *env)
{
	t_list	*p;
	t_list	*pp;
	t_list	*l;
	int		flg;

	p = NULL;
	flg = 0;
	l = tk;
	while (tk)
	{
		if (tk->type == TOKEN_SPACE)
			flg = 0;
		else if (tk->type != TOKEN_D_Q
			&& tk->type != TOKEN_S_Q && tk->type != TOKEN_SPACE)
		{
			tk->token = chck(tk, tk->token);
			flg = func2(tk, &p, &pp);
		}
		tk = tk->next;
	}
	return (syntax_check(p, env));
}

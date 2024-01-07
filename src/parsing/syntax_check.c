/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:44:22 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 12:25:22 by mozennou         ###   ########.fr       */
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

// static	int	func1(t_list **tk, t_list **p, t_list **pp, int flg)
// {
// 	if (flg == 0)
// 	{
// 		ft_lstadd_back(p, ft_lstnew(ft_strdup((*tk)->token), TOKEN_EXPR));
// 		*pp = ft_lstlast(*p);
// 		(*pp)->expand = (*tk)->expand;
// 		(*pp)->pos = (*tk)->pos;
// 		return (1);
// 	}
// 	else if (p)
// 	{
// 		(*pp) = ft_lstlast(*p);
// 		(*pp)->token = ft_strjoin((*pp)->token, (*tk)->token);
// 		if (!(*pp)->expand)
// 			(*pp)->expand = (*tk)->expand;
// 		(*pp)->pos = (*tk)->pos;
// 	}
// 	return (flg);
// }

static int	func2(t_list *tk, t_list **p, t_list **pp)
{
	ft_lstadd_back(p, ft_lstnew(ft_strdup(tk->token), tk->type));
	(*pp) = ft_lstlast(*p);
	(*pp)->expand = tk->expand;
	(*pp)->pos = tk->pos;
	return (0);
}

static int	chck(t_list *tk)
{
	if (!ft_strncmp(tk->token, "$", 2) && tk->next
		&& (tk->next->type == TOKEN_D_Q || tk->next->type == TOKEN_S_Q))
		return (0);
	return (1);
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
			&& tk->type != TOKEN_S_Q && tk->type != TOKEN_SPACE && chck(tk))
			flg = func2(tk, &p, &pp);
		// else if (tk->type != TOKEN_D_Q && tk->type != TOKEN_S_Q
		// 	&& tk->type != TOKEN_SPACE && chck(tk))
		// 	flg = func1(&tk, &p, &pp, flg);
		tk = tk->next;
	}
	return (syntax_check(p, env));
}

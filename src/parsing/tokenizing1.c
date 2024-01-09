/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:14:27 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 15:24:13 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_space(t_list **tokens, int flg)
{
	if (flg)
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(" "), TOKEN_SPACE));
	return (0);
}

static int	func4(t_list *p, int mode)
{
	if (!mode)
	{
		if (!p->next->next || p->next->next->type == TOKEN_SPACE
			|| (p->next->next->type != TOKEN_EXPR
				&& p->next->type != TOKEN_S_Q && p->next->type != TOKEN_D_Q))
			return (2);
		else
			return (1);
	}
	else
	{
		if (!p->next || p->next->type != TOKEN_EXPR)
			return (2);
		else
			return (1);
	}
	return (0);
}

t_list	*in_out(t_list *tokens)
{
	t_list	*p;
	t_list	*pp;

	p = tokens;
	pp = NULL;
	while (p)
	{
		if (p->type == TOKEN_EXPR)
		{
			if (p->next && (p->next->type == TOKEN_D_Q
					|| p->next->type == TOKEN_S_Q))
				p->pos = func4(p, 0);
			else if (pp && (pp->type == TOKEN_D_Q || pp->type == TOKEN_S_Q))
				p->pos = func4(p, 1);
			else
				p->pos = 0;
		}
		else
			p->pos = 0;
		pp = p;
		p = p->next;
	}
	return (tokens);
}

t_list	*relink(t_list *p, t_env *env)
{
	t_list	*pp;
	t_list	*cpy;

	cpy = p;
	pp = NULL;
	while (cpy)
	{
		if (!cpy->pos && (ft_strchr(cpy->token, '\\')
				|| ft_strchr(cpy->token, ';')))
			return (ft_putsyntax_error(env));
		cpy->prev = pp;
		cpy->visited = 0;
		pp = cpy;
		cpy = cpy->next;
	}
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:44:22 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/21 21:55:56 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_space(t_list **tokens, int flg)
{
	if (flg)
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(" "), TOKEN_SPACE));
	return (0);
}

void	in_out(t_list *tokens)
{
	t_list	*p;
	t_list	*pp;
	int		inquotes;

	inquotes = 0;
	p = tokens;
	pp = NULL;
	while (p)
	{
		if (p->type == TOKEN_EXPR)
		{
			if (p->next
				&& (p->next->type == TOKEN_D_Q || p->next->type == TOKEN_S_Q))
				p->pos = 1;
			else if (pp && (pp->type == TOKEN_D_Q || pp->type == TOKEN_S_Q))
				p->pos = 1;
			else
				p->pos = 0;
		}
		else
			p->pos = 0;
		pp = p;
		p = p->next;
	}
}

int	is_valid(t_list *a, t_list *b, int f)
{
	int	l;

	if (f)
		return (1);
	if (!a)
	{
		if (func6(b->type))
			return (1);
	}
	else if (!b)
	{
		if (func4(a->type))
			return (1);
	}
	else
	{
		l = func3(b->type, a->type);
		if (l)
			return (1);
	}
	return (0);
}

t_list	*relink(t_list *p)
{
	t_list	*pp;
	t_list	*cpy;

	cpy = p;
	pp = NULL;
	while (cpy)
	{
		if (pp)
			cpy->prev = pp;
		cpy->visited = 0;
		pp = cpy;
		cpy = cpy->next;
	}
	return (p);
}

t_list	*syntax_check(t_list *p)
{
	t_list	*cpy;
	t_list	*pp;
	int		f;

	cpy = p;
	pp = NULL;
	f = 0;
	while (cpy)
	{
		if (cpy->type == TOKEN_BRKT_OPEN)
			f++;
		else if (cpy->type == TOKEN_BRKT_CLOSE)
			f--;
		if (f < 0 || ft_strchr(cpy->token, ';'))
			return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
		if (is_valid(pp, cpy, 0))
			return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
		pp = cpy;
		cpy = cpy->next;
	}
	if (is_valid(pp, NULL, f))
		return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
	return (relink(p));
}
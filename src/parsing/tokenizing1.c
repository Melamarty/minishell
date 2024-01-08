/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:26:10 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/08 10:51:42 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_space(t_list **tokens, int flg)
{
	if (flg)
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(" "), TOKEN_SPACE));
	return (0);
}

t_list    *in_out(t_list *tokens)
{
    t_list    *p;
    t_list    *pp;

    p = tokens;
    pp = NULL;
    while (p)
    {
        if (p->type == TOKEN_EXPR)
        {
            if (p->next
                && (p->next->type == TOKEN_D_Q || p->next->type == TOKEN_S_Q))
            {
                if (!p->next->next || p->next->next->type != TOKEN_EXPR)
                    p->pos = 2;
                else
                    p->pos = 1;
            }
            else if (pp && (pp->type == TOKEN_D_Q || pp->type == TOKEN_S_Q))
            {
                if (!p->next || p->next->type != TOKEN_EXPR)
                    p->pos = 2;
                else
                    p->pos = 1;
            }
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

t_list	*relink(t_list *p)
{
	t_list	*pp;
	t_list	*cpy;

	cpy = p;
	pp = NULL;
	while (cpy)
	{
		cpy->prev = pp;
		cpy->visited = 0;
		pp = cpy;
		cpy = cpy->next;
	}
	return (p);
}

static int	func5(int l, int *i, int *flg)
{
	if (l == TOKEN_SPACE)
	{
		*flg = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int	func333(int l, int *i, int *flg, t_list **tokens)
{
	if (func5(l, i, flg))
		return (1);
	*flg = set_space(tokens, *flg);
	return (0);
}

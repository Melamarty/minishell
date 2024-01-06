/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:45:56 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/05 15:24:14 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_expr(char *s)
{
	char	*res;
	int		l;

	l = 0;
	while (s[l] && !is_special(s + l))
		l++;
	res = my_malloc(l + 1, 0);
	l = 0;
	while (s[l] && !is_special(s + l))
	{
		res[l] = s[l];
		l++;
	}
	res[l] = 0;
	return (res);
}

t_list	*tokenizing(char *expr, t_env *env)
{
	t_list	*tokens;
	t_list	*p;
	int		in;

	tokens = get_tokens(expr, 0);
	if (!tokens)
		return (NULL);
	in = 0;
	p = tokens;
	while (p)
	{
		if (p->type == TOKEN_S_Q)
		{
			if (!in)
				in = 1;
			else
				in = 0;
		}
		if (p->type == TOKEN_EXPR && ft_strchr(p->token, '$') && !in)
			p->expand = 1;
		else
			p->expand = 0;
		p = p->next;
	}
	return (out_of_quotes(in_out(tokens), env));
}

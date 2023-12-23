/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:45:56 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/23 21:43:44 by mozennou         ###   ########.fr       */
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
	res = malloc(l + 1);
	l = 0;
	while (s[l] && !is_special(s + l))
	{
		res[l] = s[l];
		l++;
	}
	res[l] = 0;
	return (res);
}

static int	valid(char *s)
{
	int	i;

	i = 0;
	if (!ft_strchr(s, '$'))
		return (0);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == ' ' || s[i + 1] == '\t'
				|| s[i + 1] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

t_list	*tokenizing(char *expr)
{
	t_list	*tokens;
	t_list	*p;
	int		in;

	tokens = get_tokens(expr);
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
		if (p->type == TOKEN_EXPR && valid(p->token) && !in)
			p->expand = 1;
		else
			p->expand = 0;
		p = p->next;
	}
	return (out_of_quotes(in_out(tokens)));
}

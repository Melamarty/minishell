/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:42:04 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/22 10:02:42 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	func33(int type1, int type2)
{
	if (type2 == TOKEN_PIPE && type1 == TOKEN_PIPE)
		return (type1);
	if (type2 == TOKEN_OR && type1 == TOKEN_OR)
		return (type1);
	if (type2 == TOKEN_AND && type1 == TOKEN_AND)
		return (type1);
	if (type2 == TOKEN_REDIR_IN && type1 == TOKEN_REDIR_IN)
		return (type1);
	if (type1 == TOKEN_EXPR || type2 == TOKEN_EXPR)
		return (0);
	if (type1 == TOKEN_BRKT_CLOSE || type2 == TOKEN_BRKT_CLOSE)
		return (0);
	if (type1 == TOKEN_BRKT_OPEN || type2 == TOKEN_BRKT_OPEN)
		return (0);
	if (type1 != type2)
		return (type1);
	return (0);
}

static	int	func3(int type1, int type2)
{
	if (type2 == TOKEN_BRKT_OPEN && type1 == TOKEN_BRKT_CLOSE)
		return (type2);
	if (type1 == TOKEN_BRKT_OPEN && type2 == TOKEN_BRKT_CLOSE)
		return (type1);
	if (type1 == TOKEN_BRKT_CLOSE && (is_hight(type2)))
		return (type1);
	if (type2 == TOKEN_BRKT_CLOSE && type1 == TOKEN_EXPR)
		return (type2);
	if (type2 == TOKEN_BRKT_OPEN && (is_hight(type1)))
		return (type2);
	if (type1 == TOKEN_BRKT_OPEN && type2 == TOKEN_EXPR)
		return (type1);
	if (type2 == TOKEN_HEREDOC && type1 == TOKEN_HEREDOC)
		return (type1);
	if (type2 == TOKEN_REDIR_APPEND && type1 == TOKEN_REDIR_APPEND)
		return (type1);
	if (type2 == TOKEN_REDIR_IN && type1 == TOKEN_REDIR_IN)
		return (type1);
	if (type2 == TOKEN_REDIR_OUT && type1 == TOKEN_REDIR_OUT)
		return (type1);
	return (func33(type1, type2));
}

static int	func4(int l)
{
	if (l == TOKEN_AND || l == TOKEN_OR || l == TOKEN_PIPE || l == TOKEN_HEREDOC
		|| l == TOKEN_REDIR_APPEND || l == TOKEN_REDIR_OUT
		|| l == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

static int	func6(int l)
{
	if (l == TOKEN_AND || l == TOKEN_OR || l == TOKEN_PIPE)
		return (1);
	return (0);
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

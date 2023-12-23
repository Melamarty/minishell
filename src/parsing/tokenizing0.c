/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:49:39 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/23 15:27:19 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_special(int l)
{
	if (l == TOKEN_OR)
		return (ft_strdup("||"));
	else if (l == TOKEN_AND)
		return (ft_strdup("&&"));
	else if (l == TOKEN_REDIR_APPEND)
		return (ft_strdup(">>"));
	else if (l == TOKEN_HEREDOC)
		return (ft_strdup("<<"));
	else if (l == TOKEN_PIPE)
		return (ft_strdup("|"));
	else if (l == TOKEN_BRKT_OPEN)
		return (ft_strdup("("));
	else if (l == TOKEN_BRKT_CLOSE)
		return (ft_strdup(")"));
	else if (l == TOKEN_REDIR_IN)
		return (ft_strdup("<"));
	else if (l == TOKEN_REDIR_OUT)
		return (ft_strdup(">"));
	else if (l == TOKEN_D_Q)
		return (ft_strdup("\""));
	else if (l == TOKEN_S_Q)
		return (ft_strdup("\'"));
	else if (l == TOKEN_SPACE)
		return (ft_strdup(" "));
	return (NULL);
}

static int	func5(char *s, int l, int *i, int *flg)
{
	if (l == TOKEN_SPACE)
	{
		*flg = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	func9(t_list **tokens, int flg, int i, char *expr)
{
	int	res;

	res = set_space(tokens, flg);
	ft_lstadd_back(tokens, ft_lstnew(ft_get_expr(expr + i), TOKEN_EXPR));
	return (res);
}

static int	func(int inquotes, int *i, t_list **tokens, char *expr)
{
	int		l;
	char	*arg;

	l = is_special(expr + *i);
	if ((l == TOKEN_D_Q || l == TOKEN_S_Q) && !inquotes)
	{
		(*i)++;
		arg = get_arg(expr + (*i), l);
		if (!arg)
			return (-1);
		ft_lstadd_back(tokens, ft_lstnew(get_arg(expr + (*i), l), TOKEN_EXPR));
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')
		|| (c >= '0' && c <= '9') || c == '-' || c == '$')
		return (1);
	return (0);
}

static void	func0(char *res, char *s)
{
	int	flg;
	int	l;

	l = 0;
	flg = 0;
	while (s[l] && (!is_special(s + l) || is_special(s + l) == 101)
		&& ft_isalnum(s[l]))
	{
		if (s[l] == '$')
		{
			if (!flg)
				flg = 1;
			else
				break ;
		}
		res[l] = s[l];
		l++;
	}
	res[l] = 0;
}

char	*ft_get_env(char *s)
{
	char	*res;
	int		l;
	int		flg;

	flg = 0;
	l = 0;
	if (s[l + 1] == '?')
		return (ft_strdup("$?"));
	else if (s[l + 1] == '$')
		return (ft_strdup("$$"));
	while (s[l] && (!is_special(s + l) || is_special(s + l) == 101)
		&& ft_isalnum(s[l]))
	{
		if (s[l++] == '$')
		{
			if (!flg)
				flg = 1;
			else
				break ;
		}
	}
	res = malloc(l + 1);
	if (!res)
		return (NULL);
	func0(res, s);
	return (res);
}

t_list	*get_tokens(char *expr)
{
	t_list	*tokens;
	int		flg;
	int		inquotes;
	int		i;
	int		l;

	i = 0;
	flg = 0;
	inquotes = 0;
	tokens = NULL;
	while (expr[i])
	{
		l = is_special(expr + i);
		if (l == -1)
			return (ft_lstclear(&tokens, free), ft_putsyntax_error(NULL));
		if (l && l != 101)
		{
			if (func5(expr, l, &i, &flg))
				continue ;
			flg = set_space(&tokens, flg);
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_special(l), l));
			inquotes = func(inquotes, &i, &tokens, expr);
			if (inquotes == -1)
				return (ft_lstclear(&tokens, free), ft_putsyntax_error(NULL));
		}
		else if (l == 101)
		{
			flg = set_space(&tokens, flg);
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_env(expr + i), TOKEN_EXPR));
		}
		else
			flg = func9(&tokens, flg, i, expr);
		i += ft_strlen(ft_lstlast(tokens)->token);
	}
	return (tokens);
}

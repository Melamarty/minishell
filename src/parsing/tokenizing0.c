/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:49:39 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 12:25:18 by mel-amar         ###   ########.fr       */
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

static void	set_it(int *i, int *flg, int *inquotes, t_list **tokens)
{
	*i = 0;
	*flg = 0;
	*inquotes = 0;
	*tokens = NULL;
}

t_list	*get_tokens(char *expr, int i, t_env *env)
{
	t_list	*tokens;
	int		flg;
	int		inquotes;
	int		l;

	set_it(&i, &flg, &inquotes, &tokens);
	while (expr[i])
	{
		l = is_special(expr + i);
		if (l == -1)
			return (ft_putsyntax_error(env));
		if (l)
		{
			if (func333(l, &i, &flg, &tokens))
				continue ;
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_special(l), l));
			inquotes = func(inquotes, &i, &tokens, expr);
			if (inquotes == -1)
				return (ft_putsyntax_error(env));
		}
		else
			flg = func9(&tokens, flg, i, expr);
		i += ft_strlen(ft_lstlast(tokens)->token);
	}
	return (tokens);
}

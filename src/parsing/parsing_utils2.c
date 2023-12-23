/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:39:40 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/23 14:07:38 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*pp;

	i = 0;
	p = (unsigned char *)a;
	pp = (unsigned char *)b;
	while (i < n && (p[i] || pp[i]))
	{
		if (p[i] != pp[i])
			return (p[i] - pp[i]);
		i++;
	}
	return (0);
}

void	*ft_putsyntax_error(char *s)
{
	if (!s)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	free(s);
	return (NULL);
}

char	*get_arg(char *s, int l)
{
	int		i;
	char	*res;
	char	c;

	i = 0;
	if (l == TOKEN_D_Q)
		c = '\"';
	else
		c = '\'';
	while (s[i] && s[i] != c)
		i++;
	res = malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	if (s[i] == '\0')
		return (NULL);
	res[i] = 0;
	return (res);
}

int	func_is_special(char *s)
{
	if (*s == '>')
		return (TOKEN_REDIR_OUT);
	else if (*s == '\"')
		return (TOKEN_D_Q);
	else if (*s == '\'')
		return (TOKEN_S_Q);
	else if (*s == ' ' || *s == '\t')
		return (TOKEN_SPACE);
	return (TOKEN_EXPR);
}

int	is_special(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (TOKEN_OR);
	else if (!ft_strncmp(s, "&&", 2))
		return (TOKEN_AND);
	else if (*s == '&')
		return (-1);
	else if (!ft_strncmp(s, ">>", 2))
		return (TOKEN_REDIR_APPEND);
	else if (!ft_strncmp(s, "<<", 2))
		return (TOKEN_HEREDOC);
	else if (*s == '|')
		return (TOKEN_PIPE);
	else if (*s == '(')
		return (TOKEN_BRKT_OPEN);
	else if (*s == ')')
		return (TOKEN_BRKT_CLOSE);
	else if (*s == '<')
		return (TOKEN_REDIR_IN);
	else if (*s == '$')
		return (101);
	return (func_is_special(s));
}

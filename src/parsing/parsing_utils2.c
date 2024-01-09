/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:39:40 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 12:27:02 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*ft_putsyntax_error(t_env *env)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	env->last_exit = 258;
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
	res = my_malloc(i + 1, 0);
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
	return (func_is_special(s));
}

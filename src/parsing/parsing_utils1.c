/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:37:51 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/05 13:07:21 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
		p[i++] = '\0';
}

void	*ft_calloc(size_t n, size_t s)
{
	void	*res;

	if ((int)n < 0 && (int)s < 0)
		return (NULL);
	res = my_malloc(n * s, 0);
	if (!res)
		return (NULL);
	ft_bzero(res, s * n);
	return (res);
}

int	is_hight(int type)
{
	if (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE)
		return (1);
	else if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN)
		return (2);
	return (0);
}

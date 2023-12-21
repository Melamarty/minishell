/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:37:51 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/21 20:39:54 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
	res = malloc(n * s);
	if (!res)
		return (NULL);
	ft_bzero(res, s * n);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t ln)
{
	size_t	n;
	size_t	i;
	char	*res;

	n = 0;
	i = -1;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	while (s[start + n] && n < ln)
		n++;
	res = (char *)malloc(n + 1);
	if (res == NULL)
		return (NULL);
	while (++i < n)
		res[i] = s[start + i];
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen((char *)s);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (++i < len)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

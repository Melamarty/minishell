/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:25 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/08 11:37:42 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isa(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	cw(char const *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && isa(s[i]))
			i++;
		if (s[i])
			res++;
		while (s[i] && !isa(s[i]))
			i++;
	}
	return (res);
}

static int	func2(const char **s)
{
	int	res;

	while (**s && isa(**s))
		(*s)++;
	res = 0;
	while ((*s)[res] && !isa((*s)[res]))
		res++;
	return (res);
}

static char	**ft_free(char **res, int l)
{
	while (l >= 0)
		free(res[l--]);
	free(res);
	return (NULL);
}

char	**my_split(char const *s)
{
	char	**res;
	int		i;
	int		l;

	if (!s)
		return (NULL);
	l = 0;
	res = (char **)malloc(sizeof(char *) * (cw(s) + 1));
	if (res == NULL)
		return (NULL);
	while (*s)
	{
		i = func2(&s);
		if (i > 0)
		{
			res[l] = (char *)malloc((i + 1) * sizeof(char));
			if (!res[l])
				return (ft_free(res, l - 1));
			ft_memcpy(res[l], s, i);
			res[l++][i] = '\0';
			s += i;
		}
	}
	res[l] = 0;
	return (res);
}
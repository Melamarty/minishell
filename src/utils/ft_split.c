/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:55:02 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:41:51 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)my_malloc(len + 1, 0);
	if (word == NULL)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	*ft_free(char **arr, int n)
{
	int	i;

	i = 0;
	(void)n;
	(void)arr;
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char	**spl;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	spl = (char **)my_malloc((count_words(s, c) + 1) * sizeof(char *), 0);
	if (spl == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			spl[i++] = get_word(s, c);
			if (!spl[i - 1])
				return (ft_free(spl, i - 1));
			while (*s && *s != c)
				s++;
		}
	}
	spl[i] = NULL;
	return (spl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:49:07 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:51:37 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		s1 = ft_strdup("");
	if (s2 == NULL)
		s2 = "";
	str = (char *)my_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// char	*ft_strjoin2(char *s1,char *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	if(!s1 && !s2)
// 		return (NULL);
// 	if (s1 == NULL)
// 		s1 = ft_strdup("");
// 	if (s2 == NULL)
// 		s2 = "";
// 	str = (char *)my_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0);
// 	if (!str)
// 		return NULL;
// 	i = 0;
// 	j = 0;
// 	while(s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}  
// 	while(s2[j])
// 		str[i++] = s2[j++];
// 	str[i] = '\0';
// 	return (str);
// }

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ft_strlen(str));
}

int	list_len(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		++len;
		lst = lst->next;
	}
	return (len);
}

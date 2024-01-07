/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:34:11 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 17:44:16 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	*ft_envlast(t_map *env)
{
	if (env)
	{
		while (env->next)
			env = env->next;
	}
	return (env);
}

int	ft_lstsize(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		lst = lst->next;
		res++;
	}
	return (res);
}

void	env_free(t_env *env)
{
	t_map	*tmp;

	while (env->env)
	{
		tmp = env->env->next;
		env->env = tmp;
	}
	while (env->ex_env)
	{
		tmp = env->ex_env->next;
		env->ex_env = tmp;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:34:00 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/01 08:55:43 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h" 

t_map	*ft_envnew(char *key, char *val)
{
	t_map	*res;

	res = my_malloc(sizeof(t_map), 0);
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->key = key;
	res->val = val;
	return (res);
}

int	ft__back(t_map **env, t_map *new)
{
	if (!env || !new)
		return (-1);
	if (*env == NULL)
		(*env) = new;
	else
		ft_envlast(*env)->next = new;
	return (0);
}

t_map	*get_env55(char **env)
{
	t_map	*res;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	res = NULL;
	while (env[i])
	{
		tmp1 = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		tmp2 = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, \
							ft_strlen(env[i]));
		ft__back(&res, ft_envnew(tmp1, tmp2));
		i++;
	}
	return (res);
}

void	swap(t_map *a, t_map *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->val;
	a->key = b->key;
	a->val = b->val;
	b->key = tmp_key;
	b->val = tmp_val;
}

t_map	*sort_env(t_map	*env)
{
	t_map	*p;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		p = env;
		while (p->next)
		{
			if (ft_strncmp(p->key, p->next->key, ft_strlen(p->key) + 1) > 0)
			{
				swap(p, p->next);
				swapped = 1;
			}
			p = p->next;
		}
	}
	return (env);
}

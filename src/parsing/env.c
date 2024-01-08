/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:34:00 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/08 10:28:18 by mel-amar         ###   ########.fr       */
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

void swap_keys(t_map *a, t_map *b)
{
	char	*tmp_key;

	tmp_key = a->key;
	a->key = b->key;
	b->key = tmp_key;
}

void swap_vals(t_map *a, t_map *b)
{
	char	*tmp_val;

	tmp_val = a->val;
	a->val = b->val;
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
				swap_keys(p, p->next);
				swap_vals(p, p->next);
				swapped = 1;
			}
			p = p->next;
		}
	}
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:42:33 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 13:46:00 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

int	env_add_back(t_map **env, char *key, char *val)
{
	t_map	*new;
	t_map	*head;

	head = NULL;
	if (*env)
		head = *env;
	new = my_malloc(sizeof(t_map), 0);
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	new->next = NULL;
	*env = ft_envlast(*env);
	if (!*env)
		*env = new;
	else
		(*env)->next = new;
	if (head)
		*env = head;
	return (1);
}

void	ft_envadd_back(t_map **lst, t_map *new)
{
	t_map	*tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	tmp = ft_envlast(*lst);
	tmp->next = new;
	tmp->next->next = NULL;
}

int	export_add_back(t_map **env, char *key)
{
	t_map	*new;

	new = my_malloc(sizeof(t_map), 0);
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	if (!new->key)
		return (0);
	ft_envadd_back(env, new);
	return (1);
}

int	is_exist(t_map *env, char *key)
{
	if (!env)
		return (0);
	while (env && ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		return (1);
	return (0);
}

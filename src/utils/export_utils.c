/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:40:57 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/08 10:50:51 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_map *env, t_map *ex_env)
{
	while (env)
	{
		write (1, "declare -x ", 11);
		write (1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write (1, "\"", 1);
		write (1, env->val, ft_strlen(env->val));
		write (1, "\"", 1);
		write(1, "\n", 1);
		env = env->next;
	}
	sort_ex_env(&ex_env);
	while (ex_env)
	{
		write (1, "declare -x ", 11);
		write (1, ex_env->key, ft_strlen(ex_env->key));
		write(1, "\n", 1);
		ex_env = ex_env->next;
	}
	return (1);
}

t_map	*env_new_node(char *key, char *val)
{
	t_map	*res;

	res = (t_map *)my_malloc(sizeof(t_map), 0);
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->key = key;
	res->val = val;
	return (res);
}

int	add_back(t_map **env, t_map *new)
{
	if (!env || !new)
		return (-1);
	if (*env == NULL)
		(*env) = new;
	else
		ft_envlast(*env)->next = new;
	return (0);
}

t_map	*duplicate_env(t_env *envr)
{
	t_map	*res;
	t_map	*tmp;
	t_map	*env;
	t_map	*ex_env;

	res = NULL;
	env = envr->env;
	while (env)
	{
		tmp = env_new_node(env->key, env->val);
		add_back(&res, tmp);
		env = env->next;
	}
	ex_env = envr->ex_env;
	while (ex_env)
	{
		tmp = env_new_node(ex_env->key, NULL);
		add_back(&res, tmp);
		ex_env = ex_env->next;
	}
	return (res);
}

int	print_export_env(t_env **envr)
{
	t_map	*tmp;
	t_map	*sorted;

	tmp = NULL;
	sorted = NULL;
	if ((*envr)->env)
	{
		tmp = duplicate_env(*envr);
		sorted = sort_env(tmp);
	}
	print_export(sorted, (*envr)->ex_env);
	return (1);
}

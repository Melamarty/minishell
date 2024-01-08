/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:45:53 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/08 11:10:45 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *envr, char *key)
{
	t_map	*env;

	env = envr->env;
	if (!env)
		return (ft_strdup(""));
	while (env && ft_strcmp(env->key, key))
		env = env->next;
	if (!env)
		return ("");
	return (env->val);
}

char	**set_args(char *file, t_list *args)
{
	char	**e_args;
	int		args_len;
	int		i;

	args_len = list_len(args);
	e_args = my_malloc((args_len + 2) * sizeof(char *), 0);
	i = 1;
	e_args[0] = file;
	while (args)
	{
		e_args[i++] = args->token;
		args = args->next;
	}
	e_args[i] = NULL;
	return (e_args);
}

int	map_len(t_map *map)
{
	int		i;

	i = 0;
	while (map)
	{
		++i;
		map = map->next;
	}
	return (i);
}

char	**set_env(t_env *env_list)
{
	char	**env;
	t_map	*tmp;
	int		i;

	tmp = env_list->env;
	i = 0;
	env = my_malloc(map_len(tmp) * sizeof(char *) + 1, 0);
	while (tmp)
	{
		// if (!ft_strcmp(tmp->key, "SHLVL"))
		// 	tmp->val = ft_itoa(ft_atoi(tmp->val) + 1);
		env[i] = ft_strjoin(tmp->key, "=");
		env[i] = ft_strjoin(env[i], tmp->val);
		tmp = tmp->next;
		++i;
	}
	env[i] = NULL;
	return (env);
}

char	*locate_cmd(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*ftmp;
	int		i;

	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		ftmp = paths[i];
		tmp = ft_strjoin(paths[i], "/");
		ftmp = tmp;
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

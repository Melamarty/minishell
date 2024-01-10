/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:36:52 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 13:08:41 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_err(int flag, char *path)
{
	if (flag)
	{
		write (2, "cd: ", 4);
		write (2, "error retrieving current directory: getcwd: ", 44);
		write (2, "cannot access parent directories: ", 34);
		write (2, "No such file or directory\n", 26);
	}
	else
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
	}
}

int	special_path(char *path, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!path || path[0] == '~')
		tmp = get_env(env, "HOME");
	if (tmp && !ft_strlen (tmp))
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		env->last_exit = 1;
		return (0);
	}
	else if (path[0] == '-')
		tmp = get_env(env, "OLDPWD");
	if (tmp && !ft_strlen(tmp))
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		env->last_exit = 1;
		return (0);
	}
	if (!chdir (tmp))
		return (env->last_exit = 0, 1);
	cd_err(0, path);
	env->last_exit = 1;
	return (0);
}

void	set_env_(t_env *env, char *key, char *value)
{
	t_map	*tmp;

	tmp = env->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			tmp->val = value;
			return ;
		}
		tmp = tmp->next;
	}
	env_add_back(&env->env, key, value);
}

int	update_env(t_env *env, char *path)
{
	char	*tmp;
	char	*tmp2;
	char	*jp;

	tmp = getcwd(NULL, 0);
	tmp2 = get_env(env, "PWD");
	set_env_(env, "OLDPWD", tmp2);
	if (!tmp)
	{
		jp = ft_strjoin(tmp2, "/");
		jp = ft_strjoin(jp, path);
		set_env_(env, "PWD", jp);
		cd_err(1, NULL);
		if (tmp)
			free(tmp);
		env->last_exit = 1;
		return (0);
	}
	else
		set_env_(env, "PWD", tmp);
	if (tmp)
		free(tmp);
	return (1);
}

int	cd(t_cmd *cmd, t_env *env)
{
	int		res;
	char	*path;

	path = NULL;
	if (cmd->args)
		path = cmd->args->token;
	if (!path)
		return (special_path(NULL, env), update_env(env, path));
	else if (!ft_strlen(path))
		return (update_env(env, NULL), env->last_exit = 0, 1);
	else if ((path[0] == '~' && !cmd->args->expand) || path[0] == '-')
		return (special_path(path, env), update_env(env, path));
	res = chdir(path);
	if (!update_env(env, path))
		return (0);
	if (!res)
		return (env->last_exit = 0, 1);
	cd_err(0, path);
	env->last_exit = 1;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:36:43 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 10:28:24 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_status(int pid, t_env *env)
{
	int	status;

	g_sig = -1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		env->last_exit = status;
		return (!status);
	}
	else
		return (-1);
}

int	exec_system(t_cmd *cmd, t_env *env, char *file)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmd->cmd, cmd->e_args, set_env (env)) == -1)
		{
			put_err(file, 0);
			exit(126);
		}
	}
	else
		return (get_status (pid, env));
	return (-1);
}

int	root_cmd(t_cmd *cmd, t_env *env, char *tmp)
{
	char	*file;
	char	*path;

	if (cmd->cmd[0] == '.')
	{
		path = getcwd(NULL, 0);
		file = ft_strjoin(path, cmd->cmd + 1);
		if (path)
			free(path);
		cmd->cmd = file;
	}
	else
		file = cmd->cmd;
	cmd->e_args = set_args(file, cmd->args);
	if (access(cmd->cmd, F_OK) == 0)
		return (exec_system(cmd, env, tmp));
	else
		return (env->last_exit = 127, put_err(tmp, 1));
}

int	exec_file(t_cmd *cmd, t_env *env)
{
	char	*file;
	char	*tmp;

	tmp = ft_strdup(cmd->cmd);
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
		return (root_cmd(cmd, env, tmp));
	file = locate_cmd(cmd->cmd, get_env(env, "PATH"));
	if (! ft_strlen (get_env(env, "PATH")) && access(cmd->cmd, F_OK))
		return (env->last_exit = 127, put_err(tmp, 33));
	if (!file || !ft_strlen(tmp))
		return (env->last_exit = 127, put_err(tmp, 1));
	cmd->e_args = set_args(file, cmd->args);
	cmd->cmd = ft_strdup (file);
	return (exec_system(cmd, env, tmp));
}

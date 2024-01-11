/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_cmd.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mel-amar <mel-amar@student.1337.ma>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/01/08 14:52:40 by mel-amar		  #+#	#+#			 */
/*   Updated: 2024/01/09 15:27:34 by mel-amar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"

char	*to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

int	expand_cmd(t_cmd *cmd)
{
	if (!cmd->args)
	{
		cmd->cmd = NULL;
		return (-1);
	}
	cmd->cmd = cmd->args->token;
	cmd->args = cmd->args->next;
	return (0);
}

int	fix_cmd(t_cmd *cmd, t_env *env)
{
	if (!ft_lstlen(cmd->args))
	{
		if (expand_cmd(cmd))
			return (1);
	}
	else
	{
		cmd->args = expand_args(cmd->args, env, 0);
		if (!cmd->args)
			return (1);
		if (expand_cmd(cmd))
			return (1);
	}
	return (0);
}

int	exec_cmd(t_cmd	*cmd, t_env **envr)
{
	if (fix_cmd(cmd, *envr))
		return ((*envr)->last_exit = 0, 1);
	cmd->cmd = to_lower(cmd->cmd);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (echo(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (cd(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (pwd(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (export(cmd, envr));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (unset(envr, cmd->args));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (env(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (exit_cmd(cmd));
	else if ((ft_strlen(cmd->cmd) && cmd->expand != 1) || cmd->expand != 1)
		return (exec_file(cmd, (*envr)));
	(*envr)->last_exit = 0;
	return (0);
}

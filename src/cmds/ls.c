#include "../minishell.h"

int	ls(t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmd->cmd, cmd->args, cmd->env) == -1)
		{
			perror("execve");
			return (0);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status)
			return (0);
	}
	return (1);
}
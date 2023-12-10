#include "minishell.h"
#include <string.h>
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	put_err(char *cmd);
//int exec_cmd(t_cmd *cmd)
//{
//    pid_t pid = fork();

//    if (pid == -1)
//    {
//		perror("fork");
//		exit(EXIT_FAILURE);
//    }
//    else if (pid == 0) // Child process
//    {
//        execve(cmd->cmd, cmd->args, cmd->env);
//		free (cmd->cmd);
//		free(cmd->args[0]);
//		free(cmd->args[1]);
//		free(cmd->args);
//		free (cmd);
//        perror("execve");
//        exit(EXIT_FAILURE);
//    }
//    else // Parent process
//    {
//        int status;
//        waitpid(pid, &status, 0); // Wait for the child to finish
//    }
//    return 0;
//}


void	handel_cmd(char	*cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
	{
		while (*(cmd + 5) == ' ')
			cmd++;
		printf("%s\n", cmd + 5);
	}
	else if (!ft_strncmp(cmd, "ls", 2))
	{
		t_cmd *cmd;

		cmd = malloc(sizeof(t_tree));
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->env = NULL;
		cmd->cmd = "/bin/ls";
		cmd->args[0] = malloc(1);
		cmd->args[1] = malloc(1);
		cmd->args[0] = "/bin/ls";
		cmd->args[1] = NULL;
		cmd->args[2] = NULL;
		ls(cmd);
	}
	//else if (!ft_strncmp(cmd, "cd", 2))
	//{
	//	cd(cmd + 3);
	//}
	else
		put_err(cmd);
}

void	bash_loop()
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = readline("\e[1;32mminishell >>✗");
		if (!ft_strncmp(cmd, "exit", 4))
			break;
		write (1, "\e[1;34m", 7);
		handel_cmd(cmd);
	}
}

int main ()
{
	// char *command = "/bin/ls";
    // char *args[] = {"/bin/ls", NULL, NULL};

    // char *env[] = {NULL};

	// execve(command, args, env);
	// t_tree	*cmd;
	// cmd = malloc(sizeof(cmd));
	// cmd->cmd = command;
	// cmd->args = malloc(10 * sizeof (char *));
	// cmd->args = malloc(10);
	bash_loop();
}

void put_err(char *cmd)
{
	write(2, "minishell : ", 12);
	write(2, " command not found: ", 20);
	while (*cmd && *cmd != ' ')
	{
		write (2, cmd, 1);
		cmd++;
	}
	write(2, "\n", 1);
}
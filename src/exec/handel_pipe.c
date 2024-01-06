#include "../minishell.h"

int handel_pipe(t_tree *tree, t_env **env)
{
	int		fds[2];
	int		p1;
	int		p2;

	if (!tree)
		return (1);
	if (tree->cmd)
		return (exec_cmd(tree->cmd, env));
	pipe(fds);
	if ((p1 = fork()) == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		exec_line(&tree->left, env);
		close(fds[1]);
		exit (0);
	}
	else if ((p2 = fork()) == 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		exec_line(&tree->right, env);
		close(fds[0]);
		exit (0);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	return (1);
}

// void print_info(t_cmd *cmd)
// {
// 	printf("============\n");
// 	printf("cmd         %s\n", cmd->cmd);
// 	printf("a 1         %s\n", cmd->args[0]);
// 	printf("a 2        %s\n", cmd->args[1]);
// }

// void init(t_tree **tree)
// {
// 	int fin = 0, left;
// 	t_cmd	*cmd;

// 	*tree = NULL;
// 	while (!fin)
// 	{
// 		cmd = malloc(sizeof(cmd));
// 		cmd->cmd = malloc(30);
// 		cmd->args = malloc(sizeof(char *) * 2);
// 		cmd->args[0] = malloc(30);
// 		cmd->args[1] = malloc(30);
// 		printf("left 1 || right 0\n");
// 		scanf("%d", &left);
// 		printf("enter cmd :\n");
// 		scanf("%s", cmd->cmd);
// 		printf("enter args 0 :\n");
// 		scanf("%s", cmd->args[0]);
// 		printf("enter args 1 :\n");
// 		scanf("%s", cmd->args[1]);
// 		//print_info(cmd);
// 		add_node(tree, cmd, left);
// 		printf("if you wanna add node type \n");
// 		scanf("%d", &fin);
// 	}
// }

// int main ()
// {
// 	t_tree *tree;

// 	init(&tree);
// 	print_tree(tree);
// 	printf("=========piping=======\n");
// 	handel_pipe(tree);
// 	usleep(10000);
// 	write(1, "finished (^_^)\n", 16);
// }

// int	exec_cmdd(t_cmd	*cmd)
// {
// 	printf("===== executing =====\ncmd : %s | args : %s\n=====================\n",
// 		cmd->cmd, cmd->args[1]);
// 	int	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	if (!pid)
// 	{
// 		execve(cmd->cmd, cmd->args, NULL);
// 		return (0);
// 	}
// 	return (0);
// }
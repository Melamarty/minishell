// #include "../minishell.h"

// t_tree 	*new_node(t_cmd *cmd)
// {
// 	t_tree  *node;

// 	if (!cmd)
// 		return (NULL);
// 	node = malloc(sizeof(t_tree));
// 	node->cmd = cmd;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// void	add_node(t_tree **tree, t_cmd *cmd, int	left)
// {
// 	t_tree *tmp;

// 	tmp = *tree;
// 	if (!tmp)
// 	{
// 		tmp = new_node(cmd);
// 		*tree = tmp;
// 		return ;
// 	}
// 	printf("passed\n");
// 	if (left)
// 		add_node(&tmp->left, cmd, left);
// 	else
// 		add_node(&tmp->right, cmd, left);
// }

// //void	print_tree(t_tree	*tree)
// //{
// //	if (!tree)
// //		return;
// //	print_tree(tree->left);
// //	print_info(tree->cmd);
// //	print_tree(tree->right);
// //}

// //int	execute_cmd(t_cmd *cmd)
// //{
// //	pid_t	cmd_pid;
// //	int		status;

// //	cmd_pid = fork();
// //	if (cmd_pid == -1)
// //		return (1);
// //	if (!cmd_pid)
// //	{
// //		execve(cmd->cmd, cmd->args, cmd->env);
// //		perror("execve");
// //		exit(EXIT_FAILURE);
// //	}
// //	else
// //	{
// //		waitpid(cmd_pid, &status, 0);
// //		if (WIFEXITED(status))
// //		{
// //			if (!WIFEXITED(status))
// //				return (0);
// //		}
		
// //	}
// //	return (1);
// //}
// //int main ()
// //{
// //	t_tree	*tree;
// //	t_cmd	*cmd;

// //	cmd = malloc(sizeof(t_cmd));
// //	cmd->args = malloc(sizeof(char *) * 2);
// //	cmd->env = NULL;
// //	cmd->cmd = "/bin/echo";
// //	cmd->args[0] = malloc(1);
// //	cmd->args[1] = malloc(1);
// //	cmd->args[0] = "/bin/echo";
// //	cmd->args[1] = "hello";
// //	cmd->args[2] = NULL;
// //	execute_cmd(cmd);
// //	//if (get_)
// //	//free (cmd);
// //	//free(cmd->cmd);
// //	//tree = malloc(sizeof(t_tree));
// //	//tree = NULL;
// //	//cmd = malloc(sizeof(t_cmd));
// //	//cmd->flag = 1;
// //	//add_node(&tree, cmd, 1);
// //	//cmd = malloc(sizeof(t_cmd));
// //	//cmd->flag = 2;
// //	//add_node(&tree, cmd, 1);
// //	//cmd = malloc(sizeof(t_cmd));
// //	//cmd->flag = 3;
// //	//add_node(&tree, cmd, 0);
// //	//print_tree(tree);
// //}

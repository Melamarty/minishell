#include "parsing.h"

t_tree 	*new_node(t_cmd *cmd, int type)
{
	t_tree  *node;

	// if (!cmd)
	// 	return (NULL);
	node = malloc(sizeof(t_tree));
	node->cmd = cmd;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

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
// 	if (left)
// 		add_node(&tmp->left, cmd, left);
// 	else
// 		add_node(&tmp->right, cmd, left);
// }

void	print_tree(t_tree	*tree, int c)
{
	 int i = 0;
    if (!tree)
        return;
    print_tree(tree->right, c + 5);
    while (i < c)
    {
        printf(" ");
        i++;
    }
    if (tree->type == 5)
        printf("%c ->\n", '|');
	else if (tree->type == 7)
		printf("%s ->\n", "||");
    else if (tree->type == 6)
        printf("%s ->\n", "&&");
    else if (tree->type == 100)
        printf("%c ->\n", 'C');
    else if (tree->type == 0)
        printf("%s ->\n", tree->cmd->cmd);
    else
        printf("%d ->\n", tree->type);
	if (tree->type == 0)
	{
		t_list *tmp ;
		tmp = tree->cmd->redir_in;
		while (tmp)
		{
			printf("redir_in: %s\n", tmp->token);
			tmp = tmp->next;
		}
	}
    print_tree(tree->left, c + 5);
}

void tree_free(t_tree *tree)
{
	if (!tree)
		return ;
	tree_free(tree->left);
	tree_free(tree->right);
	if (tree->cmd)
	{
		ft_lstclear(&tree->cmd->args, free);
		ft_lstclear(&tree->cmd->redir_in, free);
		ft_lstclear(&tree->cmd->redir_out, free);
		free(tree->cmd->cmd);
		free(tree->cmd);
	}
	free(tree);
}

// int	execute_cmd(t_cmd *cmd)
// {
// 	pid_t	cmd_pid;
// 	int		status;

// 	cmd_pid = fork();
// 	if (cmd_pid == -1)
// 		return (1);
// 	if (!cmd_pid)
// 	{
// 		execve(cmd->cmd, cmd->args, cmd->env);
// 		perror("execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		waitpid(cmd_pid, &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			if (!WIFEXITED(status))
// 				return (0);
// 		}
		
// 	}
// 	return (1);
// }


#include "parsing.h"

int	level(t_list *tk)
{
	if (tk->type == TOKEN_PIPE)
		return (1);
	else if (tk->type == TOKEN_AND || tk->type == TOKEN_OR)
		return (2);
	return (0);
}

t_cmd	*set_cmd(void)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	return (cmd);
}

t_tree	*command(t_list **tokens)
{
	t_tree	*node;
	t_cmd	*cmd;
	int		l;

	l = 0;
	cmd = set_cmd();
	if (!cmd)
		exit(1);
	if ((*tokens) && (*tokens)->type == TOKEN_BRKT_OPEN)      ///////////// NON protcted
	{
		(*tokens) = (*tokens)->next;
		node = condition(tokens);
		while ((*tokens) && level(*tokens) < 1)
			(*tokens) = (*tokens)->next;
		return (node);
	}
	while ((*tokens) && level(*tokens) < 1 && (*tokens)->type != TOKEN_BRKT_CLOSE)
	{
		if ((*tokens)->type == TOKEN_BRKT_OPEN)      ///////////// NON protcted
		{
			(*tokens) = (*tokens)->next;
			node = condition(tokens);
			while ((*tokens) && level(*tokens) < 1)
				(*tokens) = (*tokens)->next;
			return (node);
		}
		if ((*tokens)->type == TOKEN_REDIR_IN)
				ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup((*tokens)->token), 0));
		else if ((*tokens)->type == TOKEN_REDIR_OUT)
				ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup((*tokens)->token), 0));
		else if ((*tokens)->type == TOKEN_EXPR)
		{
			if (l == 0)
			{
				l = 1;
				cmd->cmd = ft_strdup((*tokens)->token);
			}
			else
			{
				ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup((*tokens)->token), 0));
			}
		}
		(*tokens) = (*tokens)->next;
	}
	node = new_node(cmd, TOKEN_EXPR);
	return (node);
}
void aff_list(t_list *lst)
{
	while (lst) //////////////////////////////////////////////////////////////////////
	{
		printf("%s -((%d))-> ", lst->token, lst->type);
		lst = lst->next;
	}
	printf("\n\n");
}

int	after_brackets(t_list **tokens)
{
	while (*tokens && (*tokens)->type != TOKEN_BRKT_CLOSE)
		(*tokens) = (*tokens)->next;
	if (!*tokens)
		return (-1);
	(*tokens) = (*tokens)->next;
	return (0);
}

t_tree	*condition(t_list **tokens)
{
	t_tree	*head;
	t_tree	*right;

	if (!*tokens)
		return (NULL);
	right = pipeline(tokens);
	if ((*tokens) && ((*tokens)->type == TOKEN_OR || (*tokens)->type == TOKEN_AND))
	{
		if ((*tokens)->type == TOKEN_OR)
			head = new_node(NULL, TOKEN_OR);
		else
			head = new_node(NULL, TOKEN_AND);
	}
	else
		return (right);
	(*tokens) = (*tokens)->next;
	if (!*tokens)
		exit(1); // syntax error in case of : ls &&
	head->right = right;
	head->left = condition(tokens);
	return (head);
}

t_tree	*pipeline(t_list **tokens)
{
	t_tree	*head;
	t_tree	*right;

	if (!*tokens)
		return (NULL);
	right = command(tokens);
	if ((*tokens) && (*tokens)->type == TOKEN_PIPE)
		head = new_node(NULL, TOKEN_PIPE);
	else
		return (right);
	(*tokens) = (*tokens)->next;
	if (!*tokens)
		exit(1); // syntax error in case of : ls |
	head->left = right;
	head->right = pipeline(tokens);
	return (head);
}





// void print2DUtil(t_tree* root, int space)
// {
//     // Base case
//     if (root == NULL)
//         return;
 
//     // Increase distance between levels
//     space += 10;
 
//     // Process right child first
//     print2DUtil(root->right, space);
 
//     // Print current node after space
//     // count
//     printf("\n");
//     for (int i = 10; i < space; i++)
//         printf(" ");
//     printf("%s\n", root->cmd->cmd);
 
//     // Process left child
//     print2DUtil(root->left, space);
// }
 
// // Wrapper over print2DUtil()
// void print2Dd(t_tree* root)
// {
//     // Pass initial space count as 0
//     print2DUtil(root, 0);
// }
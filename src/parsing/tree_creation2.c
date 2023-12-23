#include "parsing.h"

int	level(t_list *tk)
{
	if (tk->type == TOKEN_PIPE)
		return (1);
	else if (tk->type == TOKEN_AND || tk->type == TOKEN_OR)
		return (2);
	return (0);
}

int	after_brackets(t_list **tokens)
{
	while (*tokens && (*tokens)->type != TOKEN_BRKT_OPEN)
		(*tokens) = (*tokens)->prev;
	(*tokens)->visited = 1;
	(*tokens) = (*tokens)->prev;
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

t_tree 	*command(t_list *tokens)
{
	t_tree	*head;
	t_cmd	*cmd;

	if (!tokens)
		return (NULL);
	cmd = set_cmd();
	if (!cmd)
		return (NULL);
	while (tokens && !level(tokens) && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_REDIR_IN)
		{
			ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup(tokens->next->token), 0));
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT)
		{
			ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup(tokens->next->token), 0));
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_EXPR)
		{
			if (!cmd->cmd)
				cmd->cmd = ft_strdup(tokens->token);
			else
				ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup(tokens->token), 0));
		}
		tokens = tokens->next;
	}
	head = new_node(cmd, TOKEN_EXPR);
	return (head);
}

void	mark_token(t_list *tokens)
{
	while (tokens->type != TOKEN_BRKT_OPEN)
		tokens = tokens->prev;
	tokens->visited = 1;
}

t_tree	*condition(t_list *tokens)
{
	t_list	*cpy;
	t_tree  *head;
	t_tree	*node;

	if (!tokens)
		return (NULL);
	while (tokens->prev && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_OR)
		{
			tokens->visited = 1;
			head = new_node(NULL, TOKEN_OR);
			head->right = pipeline(tokens->next);
			head->left = condition(tokens->prev);
			return (head);
		}
		else if (tokens->type == TOKEN_AND)
		{
			tokens->visited = 1;
			head = new_node(NULL, TOKEN_AND);
			head->right = pipeline(tokens->next);
			head->left = condition(tokens->prev);
			return (head);
		}
		else if (tokens->type == TOKEN_BRKT_CLOSE)
		{
			tokens->visited = 1;
			cpy = tokens->prev;
			mark_token(tokens);
			node = condition(tokens->prev);
			if (tokens->next)
			{
				head = new_node(NULL, tokens->next->type);
				head->left = node;
				head->right = pipeline(tokens->next->next);
				return (head);
			}
			return (node);
		}
		tokens = tokens->prev;
	}
	tokens->visited = 0;
	return (pipeline(tokens));
}

t_tree	*pipeline(t_list *tokens)
{
	t_tree	*head;
	t_tree	*left;
	t_list	*cpy;

	if (!tokens)
		return (NULL);
	cpy = tokens;
	while (tokens && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			tokens->visited = 1;
			head = new_node(NULL, TOKEN_PIPE);
			head->right = pipeline(tokens->next);
			head->left = command(cpy);
			return (head);
		}
		tokens = tokens->next;
	}
	return (command(cpy));
}
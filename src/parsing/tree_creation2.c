/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:44:16 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 13:39:33 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	func2(t_list **tokens, t_cmd *cmd)
{
	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		add_cpy(&cmd->redir_in, (*tokens)->next, TOKEN_HEREDOC, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->pos)
		{
			add_cpy(&cmd->redir_in, (*tokens)->next, TOKEN_HEREDOC, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
	else if ((*tokens)->type == TOKEN_REDIR_OUT)
	{
		add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_OUT, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->pos)
		{
			add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_OUT, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
	{
		add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_APPEND, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->pos)
		{
			add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_APPEND, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
}

t_tree	*get_redirs(t_tree *head, t_list *tokens)
{
	t_tree	*res;
	t_cmd	*cmd;

	if (!tokens || level(tokens))
		return (head);
	if (set_cmd(&cmd))
		return (NULL);
	while (tokens && !level(tokens) && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_REDIR_IN)
		{
			add_cpy(&cmd->redir_in, tokens->next, TOKEN_REDIR_IN, NULL);
			tokens = tokens->next;
			while (tokens->next && tokens->next->pos)
			{
				add_cpy(&cmd->redir_in, tokens->next, TOKEN_REDIR_IN, NULL);
				tokens = tokens->next;
			}
		}
		else
			func2(&tokens, cmd);
		tokens = tokens->next;
	}
	res = new_node(cmd, TOKEN_REDIR_IN);
	res->right = head;
	return (res);
}

static void	func(t_list *tokens, t_list **cpy, t_tree **head)
{
	tokens->visited = 1;
	(*head) = new_node(NULL, TOKEN_PIPE);
	(*head)->right = pipeline(tokens->next);
	(*head)->left = command(*cpy);
}

t_tree	*pipeline(t_list *tokens)
{
	t_tree	*head;
	t_list	*cpy;

	if (!tokens)
		return (NULL);
	cpy = tokens;
	while (tokens && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_PIPE)
			return (func(tokens, &cpy, &head), head);
		else if (tokens->type == TOKEN_BRKT_OPEN)
		{
			tokens->visited = 1;
			tokens = mark_token2(tokens, &cpy);
			if (!tokens || tokens->visited == 1)
				return (get_redirs(condition(cpy), cpy->next->next));
			head = new_node(NULL, tokens->type);
			head->left = condition(cpy);
			head->right = pipeline(tokens->next);
			return (get_redirs(head, cpy->next->next));
		}
		tokens = tokens->next;
	}
	return (command(cpy));
}

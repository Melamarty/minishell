/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:44:16 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 19:02:38 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	func2(t_list **tokens, t_cmd *cmd)
{
	t_list	*cpy;

	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		redir_add(&cmd->redir_in, (*tokens)->next->token, TOKEN_HEREDOC);
		cpy = ft_lstlast(cmd->redir_in);
		cpy->fd = (*tokens)->next->fd;
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_REDIR_OUT)
	{
		redir_add(&cmd->redir_out, (*tokens)->next->token, TOKEN_REDIR_OUT);
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
	{
		redir_add(&cmd->redir_out, (*tokens)->next->token, TOKEN_REDIR_APPEND);
		(*tokens) = (*tokens)->next;
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
	while (tokens && !level(tokens))
	{
		if (tokens->type == TOKEN_REDIR_IN)
		{
			ft_lstadd_back(&cmd->redir_in,
				ft_lstnew(ft_strdup(tokens->next->token), TOKEN_REDIR_IN));
			tokens = tokens->next;
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

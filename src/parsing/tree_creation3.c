/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:28:11 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 15:42:20 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	func(t_list **tokens, t_cmd *cmd)
{
	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		add_cpy(&cmd->redir_in, (*tokens)->next, TOKEN_HEREDOC, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->next->pos)
		{
			add_cpy(&cmd->redir_in, (*tokens)->next, TOKEN_HEREDOC, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
	{
		add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_APPEND, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->next->pos)
		{
			add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_APPEND, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
	else if ((*tokens)->type == TOKEN_EXPR)
		add_cpy(&cmd->args, *tokens, TOKEN_EXPR, NULL);
}

static void	func1(t_list **tokens, t_cmd *cmd)
{
	if ((*tokens)->type == TOKEN_REDIR_OUT)
	{
		add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_OUT, NULL);
		(*tokens) = (*tokens)->next;
		while ((*tokens)->next && (*tokens)->next->pos)
		{
			add_cpy(&cmd->redir_out, (*tokens)->next, TOKEN_REDIR_OUT, NULL);
			(*tokens) = (*tokens)->next;
		}
	}
	else
		func(tokens, cmd);
}

t_tree	*command(t_list *tokens)
{
	t_tree	*head;
	t_cmd	*cmd;

	if (!tokens || set_cmd(&cmd))
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
			func1(&tokens, cmd);
		cmd->cmd = NULL;
		tokens = tokens->next;
	}
	head = new_node(cmd, TOKEN_EXPR);
	return (head);
}

static int	func5(int l, int *i, int *flg)
{
	if (l == TOKEN_SPACE)
	{
		*flg = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int	func333(int l, int *i, int *flg, t_list **tokens)
{
	if (func5(l, i, flg))
		return (1);
	*flg = set_space(tokens, *flg);
	return (0);
}

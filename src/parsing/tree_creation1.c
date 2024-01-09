/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:43:42 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 13:38:42 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	level(t_list *tk)
{
	if (tk->type == TOKEN_PIPE)
		return (1);
	else if (tk->type == TOKEN_AND || tk->type == TOKEN_OR)
		return (2);
	return (0);
}

int	set_cmd(t_cmd **cmd)
{
	(*cmd) = my_malloc(sizeof(t_cmd), 0);
	if (!cmd)
		return (-1);
	(*cmd)->cmd = NULL;
	(*cmd)->args = NULL;
	(*cmd)->redir_in = NULL;
	(*cmd)->redir_out = NULL;
	return (0);
}

void	redir_add(t_list **lst, char *token, int type)
{
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(token), type));
}

void	add_cpy(t_list **dest, t_list *src, int type, char *str)
{
	t_list	*cpy;

	if (str)
		redir_add(dest, str, type);
	else
		redir_add(dest, src->token, type);
	cpy = ft_lstlast(*dest);
	cpy->fd = src->fd;
	cpy->expand = src->expand;
	cpy->pos = src->pos;
}

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
		else if (tokens->type == TOKEN_REDIR_OUT)
		{
			add_cpy(&cmd->redir_out, tokens->next, TOKEN_REDIR_OUT, NULL);
			tokens = tokens->next;
			while (tokens->next && tokens->next->pos)
			{
				add_cpy(&cmd->redir_out, tokens->next, TOKEN_REDIR_OUT, NULL);
				tokens = tokens->next;
			}
		}
		else
			func(&tokens, cmd);
		cmd->cmd = NULL;
		tokens = tokens->next;
	}
	head = new_node(cmd, TOKEN_EXPR);
	return (head);
}

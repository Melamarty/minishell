/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:33:09 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 12:45:05 by mozennou         ###   ########.fr       */
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

int	after_brackets(t_list **tokens)
{
	while (*tokens && (*tokens)->type != TOKEN_BRKT_OPEN)
		(*tokens) = (*tokens)->prev;
	(*tokens)->visited = 1;
	(*tokens) = (*tokens)->prev;
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

static void	func(t_list **tokens, t_cmd *cmd)
{
	t_list	*cpy;

	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup((*tokens)->next->token), TOKEN_HEREDOC));
		cpy = ft_lstlast(cmd->redir_in);
		cpy->fd = (*tokens)->next->fd;
		cpy->expand = (*tokens)->next->expand;
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
	{
		ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup((*tokens)->next->token), 1));
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_EXPR)
	{
		if (!cmd->cmd)
		{
			cmd->cmd = ft_strdup((*tokens)->token);
			cmd->expand = (*tokens)->expand;
		}
		else
		{
			ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup((*tokens)->token), 0));
			cpy = ft_lstlast(cmd->args);
			cpy->expand = (*tokens)->expand;
			cpy->pos = (*tokens)->pos;
		}
	}
}

t_tree     *command(t_list *tokens)
{
    t_tree	*head;
    t_cmd	*cmd;

    if (!tokens || set_cmd(&cmd))
        return (NULL);
    while (tokens && !level(tokens) && tokens->visited == 0)
    {
		if (tokens->type == TOKEN_REDIR_IN)
		{
			ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup(tokens->next->token), TOKEN_REDIR_IN));
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT)
		{
			ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup(tokens->next->token), 0));
			tokens = tokens->next;
		}
		else
       		func(&tokens, cmd);
        tokens = tokens->next;
    }
    head = new_node(cmd, TOKEN_EXPR);
    return (head);
}

int	to_next_brkt(t_list **tokens)
{
	int	f;

	f = 0;
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_BRKT_CLOSE)
			f++;
		else if ((*tokens)->type == TOKEN_BRKT_OPEN)
			f--;
		if (!f && (*tokens)->type == TOKEN_BRKT_OPEN)
			break ; 
		(*tokens) = (*tokens)->prev;
	}
	if ((*tokens)->prev)
		return (0);
	return (1);
}

t_tree	*condition(t_list *tokens)
{
	t_tree  *head;

	if (!tokens)
		return (NULL);
	while (tokens->prev && tokens->visited == 0)
	{
		if (tokens->type == TOKEN_OR || tokens->type == TOKEN_AND)
		{
			tokens->visited = 1;
			head = new_node(NULL, tokens->type);
			head->right = pipeline(tokens->next);
			head->left = condition(tokens->prev);
			return (head);
		}
		else if (tokens->type == TOKEN_BRKT_CLOSE)
		{
			if(to_next_brkt(&tokens))
				return (pipeline(tokens));
		}
		tokens = tokens->prev;
	}
	if (tokens->type == TOKEN_BRKT_OPEN)
		return (pipeline(tokens->next));
	tokens->visited = 0;
	return (pipeline(tokens));
}

t_tree	*get_redirs(t_tree *head, t_list *tokens)
{
	t_tree	*res;
	t_cmd	*cmd;
	t_list	*cpy;


	if (!tokens || level(tokens))
		return (head);
	if (set_cmd(&cmd))
		return (NULL);
	while (tokens && !level(tokens))
	{
		if (tokens->type == TOKEN_REDIR_IN)
        {
            ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup(tokens->next->token), TOKEN_REDIR_IN));
            tokens = tokens->next;
        }
        else if (tokens->type == TOKEN_HEREDOC)
        {
            ft_lstadd_back(&cmd->redir_in, ft_lstnew(ft_strdup(tokens->next->token), TOKEN_HEREDOC));
            cpy = ft_lstlast(cmd->redir_in);
            cpy->fd = tokens->next->fd;
            tokens = tokens->next;
        }
        else if (tokens->type == TOKEN_REDIR_OUT)
        {
            ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup(tokens->next->token), 0));
            tokens = tokens->next;
        }
        else if (tokens->type == TOKEN_REDIR_APPEND)
        {
            ft_lstadd_back(&cmd->redir_out, ft_lstnew(ft_strdup(tokens->next->token), 1));
            tokens = tokens->next;
        }
		tokens = tokens->next;
	}
	res = new_node(cmd, TOKEN_REDIR_IN);
	res->right = head;
	return (res);
}

t_list	*no_more(t_list	*tokens)
{
	while (tokens && tokens->visited == 0)
	{
		if (level(tokens) == 1)
			break ;
		tokens = tokens->next;
	}
	if (!tokens || tokens->visited == 1)
		return (NULL);
	return (tokens);
}

t_list	*mark_token2(t_list *tokens, t_list **cpy)
{
	int	f;

	f = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_BRKT_OPEN)
			f++;
		else if (tokens->type == TOKEN_BRKT_CLOSE)
			f--;
		if (!f && tokens->type == TOKEN_BRKT_CLOSE)
			break ; 
		tokens = tokens->next;
	}
	tokens->visited = 1;
	(*cpy) = tokens->prev;
	return (no_more(tokens->next));
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
		{
			tokens->visited = 1;
			head = new_node(NULL, TOKEN_PIPE);
			head->right = pipeline(tokens->next);
			head->left = command(cpy);
			return (head);
		}
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

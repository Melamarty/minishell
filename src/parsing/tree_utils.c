/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:52:59 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 15:42:09 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tree	*new_node(t_cmd *cmd, int type)
{
	t_tree	*node;

	node = my_malloc(sizeof(t_tree), 0);
	node->cmd = cmd;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
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
	t_tree	*head;

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
			if (to_next_brkt(&tokens))
				return (pipeline(tokens));
		}
		tokens = tokens->prev;
	}
	if (tokens->type == TOKEN_BRKT_OPEN)
		return (pipeline(tokens->next));
	tokens->visited = 0;
	return (pipeline(tokens));
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

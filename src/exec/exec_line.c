/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:10:03 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:10:04 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_line(t_tree **line, t_env **env)
{
	t_tree	*tree;

	tree = *line;
	if (!tree)
		return (1);
	if (tree->cmd)
	{
		if (tree->cmd->redir_in || tree->cmd->redir_out)
			return (redirect (tree, env));
		else
			return (exec_cmd(tree->cmd, env));
	}
	if (tree->type == 6)
		return (exec_line(&tree->left, env) && exec_line(&tree->right, env));
	else if (tree->type == 7)
		return (exec_line(&tree->left, env) || exec_line(&tree->right, env));
	else if (tree->type == 5)
		return (handel_pipe(tree, env));
	return (1);
}

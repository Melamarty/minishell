/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:10:01 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 15:36:49 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_cmd(t_tree *tree, int fds[2], t_env **env)
{
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	exec_line(&tree->left, env);
	close(fds[1]);
	exit (0);
}

int	seceond_cmd(t_tree *tree, int fds[2], t_env **env)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	exec_line(&tree->right, env);
	close(fds[0]);
	exit (0);
}

int	handel_pipe(t_tree *tree, t_env **env)
{
	int		fds[2];
	int		p1;
	int		p2;

	if (!tree)
		return (1);
	if (tree->cmd)
		return (exec_cmd(tree->cmd, env));
	pipe(fds);
	p1 = fork();
	if (!p1)
		first_cmd(tree, fds, env);
	p2 = fork();
	if (!p2)
		seceond_cmd(tree, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	return (1);
}

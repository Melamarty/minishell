/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:08:35 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/11 13:26:34 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_out(t_tree *tree, t_env **env)
{
	int		fd;
	t_list	*tmp;

	tmp = tree->cmd->redir_out;
	while (tmp)
	{
		if ((!ft_strlen(tmp->token) || is_starts(tmp->token)) && !tmp->pos)
			return ((*env)->last_exit = 1, ambiguous_err(tmp->token));
		if (tmp->type == 3)
			fd = my_open(tmp->token, O_CREAT | O_RDWR | O_APPEND, 0644, 0);
		else
			fd = my_open(tmp->token, O_CREAT | O_RDWR | O_TRUNC, 0644, 0);
		if (fd < 0)
			return ((*env)->last_exit = 1, file_error(tmp->token));
		tmp->fd = fd;
		tmp = tmp->next;
	}
	ft_dup2(fd, 1);
	(void)env;
	return (1);
}

int	read_fd(int fd, t_env *env)
{
	int		res_fd;
	char	*buffer;
	char	*name;
	int		cpy;

	name = ft_get_name2();
	res_fd = my_open(name, O_RDWR | O_CREAT | O_TRUNC, 0644, 0);
	cpy = my_open(name, O_RDWR | O_CREAT | O_TRUNC, 0644, 0);
	if (unlink(name) || cpy == -1 || res_fd == -1)
		return (my_malloc(0, 1), exit (1), 0);
	buffer = get_next_line(fd);
	while (buffer)
	{
		buffer[ft_strlen(buffer) - 1] = 0;
		buffer = ft_expand(buffer, env);
		write(res_fd, buffer, ft_strlen(buffer));
		buffer = get_next_line(fd);
		write (res_fd, "\n", 1);
	}
	return (cpy);
}

int	redirect_in(t_tree *tree, t_env **env)
{
	int		fd;
	t_list	*tmp;

	tmp = tree->cmd->redir_in;
	while (tmp)
	{
		if (tmp->type == 4)
			fd = tmp->fd;
		else if (ft_strlen(tmp->token) || is_starts(tmp->token))
			fd = my_open(tmp->token, O_RDONLY, 0644, 0);
		else
			return ((*env)->last_exit = 1, ambiguous_err(tmp->token));
		if (fd < 0)
			return ((*env)->last_exit = 1, file_error(tmp->token));
		tmp->fd = fd;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp->type == 4 && !tmp->expand)
		fd = read_fd(tmp->fd, *env);
	ft_dup2(fd, 0);
	return (1);
}

void	initialize(int *cpy0, int *cpy1, int *res)
{
	*cpy0 = -1;
	*cpy1 = -1;
	*res = 1;
}

int	redirect(t_tree *tree, t_env **env)
{
	int	cpy1;
	int	cpy0;
	int	res;

	initialize(&cpy0, &cpy1, &res);
	expand_redirect(tree->cmd, *env);
	if (tree->cmd->redir_in)
	{
		cpy0 = dup(0);
		res = redirect_in(tree, env);
	}
	if (tree->cmd->redir_out && res)
	{
		cpy1 = dup(1);
		res = redirect_out(tree, env);
	}
	if (res && tree->cmd)
		exec_cmd(tree->cmd, env);
	if (res && tree->right)
		exec_line (&tree->right, env);
	if (cpy1 != -1)
		ft_dup2(cpy1, 1);
	if (cpy0 != -1)
		ft_dup2(cpy0, 0);
	return (close(cpy1), close(cpy0), res);
}

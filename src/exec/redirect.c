/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:08:35 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 12:32:44 by mel-amar         ###   ########.fr       */
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
		if (tmp->type == 3)
			fd = open(tmp->token, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(tmp->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			return ((*env)->last_exit = 1, file_error(tmp->token));
		tmp->fd = fd;
		if (tmp->next)
			close(fd);
		tmp = tmp->next;
	}
	ft_dup2(fd, 1);
	close(fd);
	(void)env;
	return (1);
}

char	*ft_get_name2(void)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(".expand");
	while (!access(res, F_OK))
	{
		res = ft_strjoin(res, ft_itoa(i));
		i++;
	}
	return (res);
}

int	read_fd(int fd, t_env *env)
{
	int		res_fd;
	char	*buffer;
	char	*name;
	int		cpy;

	name = ft_get_name2();
	res_fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	cpy = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (unlink(name) || cpy == -1 || res_fd == -1)
		return (close (cpy), close (res_fd),
			close (fd), my_malloc(0, 1), exit (1), 0);
	buffer = get_next_line(fd);
	while (buffer)
	{
		buffer[ft_strlen(buffer) - 1] = 0;
		buffer = ft_expand(buffer, env);
		write(res_fd, buffer, ft_strlen(buffer));
		buffer = get_next_line(fd);
		write (res_fd, "\n", 1);
	}
	return (close (fd), close(res_fd), cpy);
}

int	redirect_in(t_tree *tree, t_env **env)
{
	int		fd;
	t_list	*tmp;

	tmp = tree->cmd->redir_in;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			fd = tmp->fd;
		else
			fd = open(tmp->token, O_RDONLY);
		if (fd < 0)
			return ((*env)->last_exit = 1, file_error(tmp->token));
		tmp->fd = fd;
		if (tmp->next)
			close(fd);
		else
			break ;
		tmp = tmp->next;
	}
	if (tmp->type == TOKEN_HEREDOC && !tmp->expand)
		fd = read_fd(tmp->fd, *env);
	ft_dup2(fd, 0);
	close(fd);
	(void)env;
	return (1);
}

void expand_redirect(t_cmd *cmd, t_env *env)
{
	if (cmd->redir_in)
		cmd->redir_in = expand_args(cmd->redir_in, env, 1);
	if (cmd->redir_out)
		cmd->redir_out = expand_args(cmd->redir_out, env, 1);
}

int	redirect(t_tree *tree, t_env **env)
{
	int	cpy1;
	int	cpy0;
	int	res;

	cpy1 = -1;
	cpy0 = -1;
	res = 1;
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

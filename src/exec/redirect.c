#include "../minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		my_malloc(0, 1);
		exit(1);
	}
}

int	redirect_out(t_tree *tree, t_env **env)
{
	int		fd;
	t_list	*tmp;
	int		cpy;

	tmp = tree->cmd->redir_out;
	while (tmp)
	{
		if (tmp->type)
			fd = open(tmp->token, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(tmp->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			return (file_error(tmp->token));
		tmp->fd = fd;
		if (tmp->next)
			close(fd);
		tmp = tmp->next;
	}
	cpy = dup(1);
	ft_dup2(fd, 1);
	close(fd);
	if (tree->cmd->cmd)
		exec_cmd(tree->cmd, env);
	ft_dup2(cpy, 1);
	return (1);
}

int	read_fd(int fd, t_env *env)
{
	int		res_fd;
	char	*buffer;
	char	*name;
	int		cpy;

	name = ft_get_name();
	res_fd = open(".expand", O_RDWR | O_CREAT | O_TRUNC, 0644);
	cpy = open(".expand", O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	int		cpy;

	tmp = tree->cmd->redir_in;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			fd = tmp->fd;
		else
			fd = open(tmp->token, O_RDONLY);
		if (fd < 0)
			return (file_error(tmp->token));
		tmp->fd = fd;
		if (tmp->next)
			close(fd);
		else
			break ;
		tmp = tmp->next;
	}
	if (tmp->type == TOKEN_HEREDOC)
		fd = read_fd(tmp->fd, *env);
	cpy = dup(0);
	ft_dup2(fd, 0);
	close(fd);
	if (tree->cmd->cmd)
		exec_cmd(tree->cmd, env);
	return (ft_dup2(cpy, 0), 0);
}

int	redirect(t_tree *tree, t_env **env)
{
	t_list	*list;

	if (tree->cmd->redir_in)
	{
		list = tree->cmd->redir_in;
		redirect_in(tree, env);
	}
	if (tree->cmd->redir_out)
	{
		list = tree->cmd->redir_out;
		redirect_out(tree, env);
	}
	return (1);
}

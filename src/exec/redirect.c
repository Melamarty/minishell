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
	ft_dup2(fd, 1);
	close(fd);
	// if (tree->cmd->cmd)
	// 	exec_cmd(tree->cmd, env);
	// if (tree->right)
	// 	exec_line(&tree->right, env);
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
		res = ft_strjoin2(res, ft_itoa(i));
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
	return (close (fd), cpy);
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
			return (file_error(tmp->token));
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
	// if (tree->cmd->cmd)
	// 	exec_cmd(tree->cmd, env);
	return (1);
}

int	redirect(t_tree *tree, t_env **env)
{
	t_list	*list;
	int cpy1 = -1;
	int cpy0 = -1;
	int res = 1;

	if (tree->cmd->redir_in)
	{
		cpy0 = dup(0);
		list = tree->cmd->redir_in;
		res = redirect_in(tree, env);
	}
	if (tree->cmd->redir_out && res)
	{
		cpy1 = dup(1);
		list = tree->cmd->redir_out;
		res = redirect_out(tree, env);
	}
	if (res && tree->cmd)
		exec_cmd(tree->cmd, env);
	if (cpy1 != -1)
		ft_dup2(cpy1, 1);
	if (cpy0 != -1)
		ft_dup2(cpy0, 0);
	close(cpy1);
	close(cpy0);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:53:08 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/23 22:04:59 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_name(void)
{
	char	*res;
	char	tmp[10];
	int		i;

	i = 0;
	res = ft_strdup(".heredoc");
	while (!access(res, F_OK))
	{
		res = ft_strjoin(res, ft_itoa(i));
		i++;
	}
	return (res);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
	}
}

int is_fd_closed(int fd)
{
    int flags = fcntl(fd, F_GETFD);
    return (flags == -1);
}

int	read_heredoc(char *limiter)
{
	int		fd;
	int		m;
	char	*name;
	char	*buffer;
	int		i;

	signal(SIGINT, sig_handler);
	name = ft_get_name();
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (unlink(name) == -1)
		return (perror("unlink"),free(name), -1);
	free(name);
	while (1)
	{
		buffer = readline("> ");
		if (!ttyname(0))
		{
			m = open(ttyname(2), O_RDWR);
			dup2(0, m);
			return (-1);
		}
		if (!buffer)
			return (fd);
		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1))
			return (fd);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (-1);
}

// int	read_heredoc(char *limiter)
// {
// 	int		fd[2];
// 	char	*buffer;
// 	int		i;

// 	if (pipe(fd) == -1)
// 		return (-1);
// 	while (1)
// 	{
// 		i = 0;
// 		buffer = readline("> ");
// 		if (!buffer)
// 			return (close(fd[0]), close(fd[1]), fd[0]);
// 		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1))
// 			return (free(buffer), close(fd[1]), fd[0]);
// 		write(fd[1], buffer, ft_strlen(buffer));
// 		free(buffer);
// 	}
// 	return (-1);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:53:08 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 17:53:44 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_name(void)
{
	char	*res;
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

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
	}
}

static void	func(t_env *env)
{
	int	m;

	m = open(ttyname(2), O_RDWR);
	if (m == -1)
		exit(1);
	ft_dup2(0, m);
	env->last_exit = 1;
}

static int	func2(int *fd1, int *fd2)
{
	char	*name;

	name = ft_get_name();
	*fd1 = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd1 == -1)
		return (-1);
	*fd2 = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (unlink(name) == -1 || *fd2 == -1)
		return (perror("unlink"), close(*fd1), -1);
	return (0);
}

int	read_heredoc(char *limiter, t_env *env)
{
	int		fd1;
	int		fd2;
	char	*buffer;

	signal(SIGINT, signal_handler);
	if (func2(&fd1, &fd2) == -1)
		return (-1);
	while (1)
	{
		buffer = readline("> ");
		if (!ttyname(0))
			return (func(env), close(fd1), close(fd2), -1);
		if (!buffer)
			return (close(fd1), fd2);
		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1))
			return ( fd2);
		buffer = ft_strjoin(buffer, "\n");
		write(fd1, buffer, ft_strlen(buffer));
	}
	return (-1);
}

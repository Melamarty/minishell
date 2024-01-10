/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:51:21 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 21:11:32 by mozennou         ###   ########.fr       */
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
	{
		my_malloc(0, 1);
		exit(1);
	}
	env->last_exit = 1;
}

static int	func2(int *fd1, int *fd2)
{
	char	*name;

	name = ft_get_name();
	*fd1 = my_open(name, O_RDWR | O_CREAT | O_TRUNC, 0644, 0);
	*fd2 = my_open(name, O_RDWR | O_CREAT | O_TRUNC, 0644, 0);
	if (unlink(name) == -1)
		return (perror("unlink"), -1);
	return (0);
}

int	read_heredoc(char *limiter, t_env *env)
{
	int		fd1;
	int		fd2;
	char	*buffer;
	char	*tmp;

	signal(SIGINT, signal_handler);
	if (func2(&fd1, &fd2) == -1)
		return (-1);
	while (1)
	{
		buffer = readline("> ");
		if (!ttyname(0))
			return (free(buffer), func(env), -1);
		if (!buffer)
			return (fd2);
		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1))
			return (free(buffer), fd2);
		tmp = buffer;
		buffer = ft_strjoin(buffer, "\n");
		write(fd1, buffer, ft_strlen(buffer));
		free(tmp);
	}
	return (-1);
}

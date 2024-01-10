/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:52:03 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/10 21:13:46 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_open(char *path, int flags, int permissions, int mode)
{
	int				fd;
	static t_adress	*fds;

	if (!mode)
	{
		fd = open(path, flags, permissions);
		if (fd == -1)
		{
			perror("minishell");
			my_malloc(0, 1);
			my_open(NULL, 0, 0, 1);
			exit(1);
		}
		ft_addr_back(&fds, ft_addrnew(NULL, fd));
		return (fd);
	}
	else
		return (ft_addr_clear(&fds), -1);
}

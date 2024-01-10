/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:52:03 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/10 22:21:30 by mozennou         ###   ########.fr       */
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
		ft_addr_back(&fds, ft_addrnew(NULL, fd));
		return (fd);
	}
	else
	{
		ft_addr_clear(&fds);
		fds = NULL;
		return (-1);
	}
}

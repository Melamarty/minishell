/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:44:03 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 20:56:54 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addr_back(t_adress **head, t_adress *new)
{
	t_adress	*tmp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_addr_clear(t_adress **head)
{
	t_adress	*tmp;

	if (!head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->fd != -1)
			close(tmp->fd);
		if (tmp->addr)
			free(tmp->addr);
		free(tmp);
	}
}

t_adress	*ft_addrnew(void *addr, int fd)
{
	t_adress	*new;

	new = malloc(sizeof(t_adress));
	if (!new)
		return (NULL);
	new->addr = addr;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	*my_malloc(size_t size, int mode)
{
	void			*ptr;
	static t_adress	*head;

	if (!mode)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_addr_clear(&head), exit(1), NULL);
		ft_addr_back(&head, ft_addrnew(ptr, -1));
		return (ptr);
	}
	else
		return (ft_addr_clear(&head), NULL);
}

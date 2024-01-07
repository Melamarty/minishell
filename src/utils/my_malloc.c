/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:44:03 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:45:44 by mel-amar         ###   ########.fr       */
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
		free(tmp->addr);
		free(tmp);
	}
}

t_adress	*ft_addrnew(void *addr)
{
	t_adress	*new;

	new = malloc(sizeof(t_adress));
	if (!new)
		return (NULL);
	new->addr = addr;
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
		ft_addr_back(&head, ft_addrnew(ptr));
		return (ptr);
	}
	else
		return (ft_addr_clear(&head), NULL);
}

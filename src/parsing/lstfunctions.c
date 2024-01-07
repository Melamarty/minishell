/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:36:38 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 17:45:26 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*res;

	res = (t_list *)my_malloc(sizeof(t_list), 0);
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->type = type;
	res->token = content;
	return (res);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return (-1);
	new->next = NULL;
	if (*lst == NULL)
		(*lst) = new;
	else
		ft_lstlast(*lst)->next = new;
	return (0);
}

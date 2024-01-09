/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:27:56 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 16:22:28 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_list(t_list **head)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*str;

	tmp = *head;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->token, tmp2->token) > 0)
			{
				str = tmp->token;
				tmp->token = tmp2->token;
				tmp2->token = str;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_list	*get_wildcard(void)
{
	DIR				*dir;
	t_list			*wild_list;
	struct dirent	*entry;

	wild_list = NULL;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (my_malloc(0, 1), exit(1), NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1))
			ft_lstadd_back(&wild_list, ft_lstnew(entry->d_name, 0));
		entry = readdir(dir);
	}
	closedir(dir);
	sort_list(&wild_list);
	return (wild_list);
}

t_list	*wildcard(t_list *args)
{
	t_list	*res;
	t_list	*tmp;
	t_list 	*tmp2;

	res = NULL;
	while (args)
	{
		if (ft_strcmp(args->token, "*") || args->expand)
		{
			ft_lstadd_back(&res, ft_lstnew(args->token, 0));
			tmp2 = ft_lstlast(res);
			tmp2->expand = args->expand;
			tmp2->type = args->type;
			tmp2->fd = args->fd;
		}
		else
		{
			tmp2 = get_wildcard();
			if (!res)
				res = tmp2;
			else
			{
				tmp = ft_lstlast(res);
				tmp->next = tmp2;
			}
		}
		args = args->next;
	}
	return (res);
}
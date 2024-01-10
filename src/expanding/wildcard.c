/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:18:05 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 11:18:06 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

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

static void	norm_helper(t_list *res, t_list *tmp, t_list *tmp2)
{
	tmp = ft_lstlast(res);
	tmp->next = tmp2;
}

static void	norm_helper2(t_list *tmp2, t_list *args)
{
	tmp2->expand = args->expand;
	tmp2->type = args->type;
	tmp2->fd = args->fd;
}

t_list	*wildcard(t_list *args)
{
	t_list	*res;
	t_list	*tmp;
	t_list	*tmp2;

	res = NULL;
	tmp = NULL;
	while (args)
	{
		if (ft_strcmp(args->token, "*") || args->expand)
		{
			ft_lstadd_back(&res, ft_lstnew(args->token, 0));
			tmp2 = ft_lstlast(res);
			norm_helper2(tmp2, args);
		}
		else
		{
			tmp2 = get_wildcard();
			if (!res)
				res = tmp2;
			else
				norm_helper(res, tmp, tmp2);
		}
		args = args->next;
	}
	return (res);
}

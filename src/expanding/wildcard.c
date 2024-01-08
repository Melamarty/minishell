#include "../minishell.h"

void sort_list (t_list **head)
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

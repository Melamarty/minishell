#include "../minishell.h"

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
	return (wild_list);
}

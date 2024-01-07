#include "../minishell.h"

int ft_lstlen(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i += ft_strlen(lst->token);
		lst = lst->next;
	}
	return (i);
}
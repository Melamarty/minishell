#include "../minishell.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
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
	if (*lst == NULL)
		(*lst) = new;
	else
		ft_lstlast(*lst)->next = new;
	return (0);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		(*del)(lst->token);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;

	if (!lst || !(del))
		return ;
	p = (*lst);
	while (*lst)
	{
		(*lst) = (*lst)->next;
		ft_lstdelone(p, del);
		p = (*lst);
	}
}

int	ft_lstsize(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		lst = lst->next;
		res++;
	}
	return (res);
}


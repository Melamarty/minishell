#include "../minishell.h"

void ft_addr_back(t_adress **head, t_adress *new)
{
	t_adress *tmp;

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
	// printf ("add %p\n", new->addr);
}

void ft_addr_clear(t_adress **head)
{
	t_adress *tmp;

	if (!head)
		return ;
	while (*head)
	{
		// printf ("free  %p index %d\n", (*head)->addr, (*head)->index);
		tmp = *head;
		*head = (*head)->next;
		free(tmp->addr);
		free(tmp);
	}
}

t_adress *ft_addrnew(void *addr)
{
	t_adress *new;
	static int i = 0;		

	new = malloc(sizeof(t_adress));
	// printf ("addr %p\n", addr);
	if (!new)
		return (NULL);
	new->addr = addr;
	new->index = i;
	// printf ("new %p index %d\n", new, new->index);
	i++;
	new->next = NULL;
	return (new);
}

void	*my_malloc(size_t size, int mode)
{
	void	*ptr;
	static t_adress *head;

	if (!mode)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_addr_clear(&head), exit(1), NULL);
		ft_addr_back(&head, ft_addrnew(ptr));
		// printf ("malloc %p\n", ptr);
		return (ptr);
	}
	else
		return (ft_addr_clear(&head), NULL);
}

#include <string.h>
// void f(void)
// {
// 	system("leaks a.out");
// }

// int main(void)
// {
// 	atexit(f);
// 	char *str = my_malloc(10, 0);
// 	char *str2 = my_malloc(10, 0);
// 	str = strcpy(str, "Hello");
// 	printf("%s %p\n", str, str);
// 	str = malloc(10);
// 	while (1)
// 		pause();
// 	return (0);
// }
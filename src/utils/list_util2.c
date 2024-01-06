#include "../minishell.h"

int	env_add_back(t_map **env, char *key, char *val)
{
	t_map	*new;
	t_map	*head;

	head = NULL;
	if (*env)
		head = *env;
	new = malloc(sizeof(t_map));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	new->next = NULL;
	*env = ft_envlast(*env);
	if (!*env)
		*env = new;
	else
		(*env)->next = new;
	if (head)
		*env = head;
	return (1);
}

void	ft_envadd_back(t_map **lst, t_map *new)
{
	t_map	*tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	tmp = ft_envlast(*lst);
	tmp->next = new;
	tmp->next->next = NULL;
}

int	export_add_back(t_map **env, char *key)
{
	t_map	*new;
	new = malloc(sizeof(t_map));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	// free (key);
	if (!new->key)
		return (0);
	ft_envadd_back(env, new);
	return (1);
}

int	is_exist(t_map *env, char *key)
{
	if (!env)
		return (0);
	while (env && ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		return (1);
	return (0);
}


//t_list *ft_lstlast(t_list *lst)
//{
//	if (!lst)
//		return (NULL);
//	if (!lst->next)
//		return (lst);
//	while (lst->next)
//		lst = lst->next;
//	return (lst);
//}

//int	ft_lstadd_back(t_list **lst, t_list *new)
//{
//	if (!lst || !new)
//		return (-1);
//	if (*lst == NULL)
//		(*lst) = new;
//	else
//		ft_lstlast(*lst)->next = new;
//	return (0);
//}

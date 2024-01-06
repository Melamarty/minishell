#include "../minishell.h"

t_map *unset_var(t_map *env, char *key)
{
	t_map *head = env;
	t_map	*prev;

	if (env && (!env->next || !ft_strcmp(env->key, key)))
	{
		prev = env;
		env = env->next;
		return (env);
	}
	while (env && key && ft_strcmp(env->key, key))
	{
		prev = env;
		env = env->next;
	}
	if (!env)
		return (head);
	if (env->next)
	{
		env = prev;
		env->next = prev->next->next;
		prev->next = NULL;
	}
	else
	{
		env = prev;
		env->next = NULL;
	}
	return (head);
}

int unset(t_env **envr, t_list *args)
{
	t_map *tmp;

	if (!args || !args->token)
		return ((*envr)->last_exit = 0, 0);
	while (args)
	{
		char *key = args->token;
		tmp = unset_var((*envr)->env, key);
		(*envr)->env = tmp;
		tmp = unset_var((*envr)->ex_env, key);
		(*envr)->ex_env = tmp;
		args = args->next;
	}
	(*envr)->last_exit = 0;
	return (1);
}

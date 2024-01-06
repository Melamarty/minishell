#include "../minishell.h"

t_map	*unset_var(t_map *env, char *key)
{
	t_map *new = NULL;
	t_map *head = NULL;
	t_map *prev = NULL;

	while (env)
	{
		if (ft_strcmp(env->key, key))
		{
			new = my_malloc(sizeof(t_map), 0);
			new->key = env->key;
			new->val = env->val;
		
			if (head == NULL)
				head = new;
			else
				prev->next = new;
			prev = new;
		}
		env = env->next;
	}
	return head;
}


int	unset(t_env **envr, t_list *args)
{
	t_map	*tmp;
	t_map 	*tmp2;
	int		i;

	if (!args || !args->token)
		return ((*envr)->last_exit = 0, 1);
	while (args)
	{
		tmp2 = parse_param(args->token, &i, *envr);
		if (tmp2)
		{
			tmp = unset_var((*envr)->env, args->token);
			(*envr)->env = tmp;
			tmp = unset_var((*envr)->ex_env, args->token);
			(*envr)->ex_env = tmp;
		}
		else
			(*envr)->last_exit = -1;
		args = args->next;
	}
	if ((*envr)->last_exit == -1)
		return ( (*envr)->last_exit = 1, 0);
	(*envr)->last_exit = 0;
	return (1);
}

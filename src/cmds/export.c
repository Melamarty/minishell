#include "../minishell.h"

void sort_ex_env(t_map **env)
{
	t_map *tmp;
	t_map *tmp2;
	char *hlp;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				hlp = tmp->key;
				tmp->key = tmp2->key;
				tmp2->key = hlp;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	print_export(t_map *env, t_map *ex_env)
{
	while (env)
	{
		write (1, "declare -x ", 11);
		write (1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write (1, "\"", 1);
		write (1, env->val, ft_strlen(env->val));
		write (1, "\"", 1);
		write(1, "\n", 1);
		env = env->next;
	}
	sort_ex_env(&ex_env);
	while (ex_env)
	{
		write (1, "declare -x ", 11);
		write (1, ex_env->key, ft_strlen(ex_env->key));
		write(1, "\n", 1);
		ex_env = ex_env->next;
	}
	return (1);
}

t_map *env_new_node(char *key, char *val)
{
	t_map	*res;

	res = (t_map *)my_malloc(sizeof(t_map), 0);
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->key = key;
	res->val = val;
	return (res);
}

int	add_back(t_map **env, t_map *new)
{
	if (!env || !new)
		return (-1);
	if (*env == NULL)
		(*env) = new;
	else
		ft_envlast(*env)->next = new;
	return (0);
}

t_map *duplicate_env(t_map *env)
{
	t_map *res;
	t_map *tmp;

	res = NULL;
	while (env)
	{
		tmp = env_new_node(env->key, env->val);
		add_back(&res, tmp);
		env = env->next;
	}
	return (res);
}

int	print_export_env(t_env **envr)
{
	t_map	*tmp;
	t_map *sorted;

	tmp = NULL;
	if ((*envr)->env)
	{
		tmp = duplicate_env((*envr)->env);
		sorted = sort_env(tmp);
	}
	//if(tmp)
	print_export(tmp, (*envr)->ex_env);
	// if (tmp)
	return (1);
}

int	change_val(t_map**env, char *key, char *val)
{
	t_map *tmp;
	char	*hlp;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	hlp = tmp->key;
	tmp->key = key;
	if (val)
	{
		hlp = tmp->val;
		tmp->val = val;
	}
	return (1);
}

void print_args(t_list *args)
{
	while (args)
	{
		printf("%s  ", args->token);
		args = args->next;
	}
}

void	append_var(t_map **env, t_map *var)
{
	t_map *tmp;
	
	tmp = *env;
	while (tmp&& ft_strcmp(tmp->key, var->key))
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp->val = ft_strjoin(tmp->val, var->val);
}

int	export_args(t_env **env, t_list *args)
{
	t_map	*var;
	int		append;
	t_list *tmp;

	while (args)
	{
		var = parse_param(args->token, &append, *env);
		if (var)
		{
			tmp = my_malloc(sizeof(t_list), 0);
			if (!tmp)
				return ((*env)->last_exit = 1, 0);
			tmp->token = var->key;
			tmp->next = NULL;
			if (append && var->val && is_exist((*env)->env, var->key))
				append_var(&(*env)->env, var);
			else
			{
				unset(env, tmp);
				if (var->val)
					env_add_back(&(*env)->env, var->key, var->val);
				else
					export_add_back(&(*env)->ex_env, var->key);
			}
		}
		args = args->next;
	}
	return (1);
}

int	export(t_cmd *cmd, t_env **env)
{
	if (!list_len(cmd->args))
		return ((*env)->last_exit = 0,print_export_env(env));
	else
		export_args(env, cmd->args);
	if ((*env)->last_exit == 33)
		return ((*env)->last_exit = 1, 0);
	(*env)->last_exit = 0;
	return 1;
}

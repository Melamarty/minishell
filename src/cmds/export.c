/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:23 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:38:06 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_ex_env(t_map **env)
{
	t_map	*tmp;
	t_map	*tmp2;
	char	*hlp;

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

void	append_var(t_map **env, t_map *var)
{
	t_map	*tmp;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->key, var->key))
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp->val = ft_strjoin(tmp->val, var->val);
}

void	add_var(t_env**env, t_map *var, t_list *tmp )
{
	unset(env, tmp);
	if (var->val)
		env_add_back(&(*env)->env, var->key, var->val);
	else
		export_add_back(&(*env)->ex_env, var->key);
}

int	export_args(t_env **env, t_list *args)
{
	t_map	*var;
	int		append;
	t_list	*tmp;

	while (args)
	{
		var = parse_param(args->token, &append, *env);
		tmp = my_malloc(sizeof(t_list), 0);
		if (var)
			tmp->token = var->key;
		tmp->next = NULL;
		if (var && append && var->val && is_exist((*env)->env, var->key))
			append_var(&(*env)->env, var);
		else if (is_exist((*env)->env, args->token) && !var->val)
			append += 0;
		else if (!append && var->val)
			env_add_back(&(*env)->env, var->key, var->val);
		else if (var)
			add_var(env, var, tmp);
		args = args->next;
	}
	return (1);
}

int	export(t_cmd *cmd, t_env **env)
{
	if (!list_len(cmd->args))
		return ((*env)->last_exit = 0, print_export_env(env));
	else
		export_args(env, cmd->args);
	if ((*env)->last_exit == 33)
		return ((*env)->last_exit = 1, 0);
	(*env)->last_exit = 0;
	return (1);
}

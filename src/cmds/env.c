/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:18 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:37:19 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_cmd *cmd, t_env *envr)
{
	t_map	*env;

	env = envr->env;
	if (!ft_strlen (get_env(envr, "PATH")))
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		envr->last_exit = 127;
		return (1);
	}
	(void )cmd;
	if (!env)
		return (1);
	while (env)
	{
		write (1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write (1, env->val, ft_strlen(env->val));
		write(1, "\n", 1);
		env = env->next;
	}
	envr->last_exit = 0;
	return (1);
}

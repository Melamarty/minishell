/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:26 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 14:39:54 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*tmp;

	if (cmd->args)
	{
		env->last_exit = 1;
		write(2, "pwd: too many arguments\n", 24);
		return (0);
	}
	path = get_env(env, "PWD");
	env->last_exit = 0;
	if (!ft_strlen(path))
	{
		tmp = getcwd(NULL, 0);
		putstr(tmp);
		free(tmp);
		return (1);
	}
	putstr(path);
	return (1);
}

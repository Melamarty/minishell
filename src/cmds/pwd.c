/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:26 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/07 17:37:27 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_cmd *cmd, t_env *env)
{
	char	path[1024];

	if (cmd->args)
	{
		env->last_exit = 1;
		write(2, "pwd: too many arguments\n", 24);
		return (0);
	}
	getcwd(path, 1024);
	putstr(path);
	env->last_exit = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:11 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 21:55:38 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	echo(t_cmd *cmd, t_env *env)
{
	t_list	*args;
	int		is_n;

	args = cmd->args;
	is_n = 0;
	if (cmd->args && cmd->args->token && is_option(cmd->args->token))
	{
		is_n = 1;
		args = args->next;
	}
	while (args && args->token && is_option(args->token))
		args = args->next;
	while (args)
	{
		ft_putstr_fd(args->token, 1);
		if (args->next)
			ft_putstr_fd(" ", 1);
		args = args->next;
	}
	if (!is_n)
		write(1, "\n", 1);
	env->last_exit = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:43:47 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/11 12:00:42 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char *s)
{
	int	pm;

	pm = 0;
	if (!*s)
		return (-1);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (-1);
	while (*s && ((*s >= '0' && *s <= '9')))
		s++;
	if (*s)
		return (-1);
	return (0);
}

static int	func(char *s, int *i)
{
	int	neg;

	neg = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[(*i)++] == '-')
			neg *= -1;
	}
	while (s[*i] && s[*i] == '0')
		(*i)++;
	return (neg);
}

int	ft_atoi2(char *s, long *num)
{
	int				i;
	int				neg;
	int				digits;
	unsigned long	res;

	digits = 0;
	if (check(s))
		return (-1);
	i = 0;
	neg = 1;
	res = 0;
	neg = func(s, &i);
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		(1) && (res = (res * 10) + (s[i++] - '0'), digits++);
	if ((neg == -1 && res - 1 > LONG_MAX) || (neg == 1 && res > LONG_MAX) || \
		digits >= 20)
		return (-1);
	return (*num = (int)(res * neg), 0);
}

void	exit_err(char *arg, int flag)
{
	write (2, "minishell: exit: ", 17);
	if (flag == 1)
	{
		write (2, arg, ft_strlen(arg));
		write (2, ": numeric argument required\n", 28);
	}
	else
		write (2, ": too many arguments\n", 21);
}

int	exit_cmd(t_cmd *cmd)
{
	long	nb;

	nb = 0;
	if (list_len(cmd->args) > 1)
	{
		if (ft_atoi2(cmd->args->token, &nb) == -1)
		{
			exit_err(cmd->args->token, 1);
			my_malloc (0, 1);
			exit(255);
		}
		exit_err(cmd->args->token, 2);
		return (0);
	}
	my_malloc (0, 1);
	printf ("segfault not in malloc\n");
	if (cmd->args)
	{
		if (ft_atoi2(cmd->args->token, &nb) == -1)
		{
			write (2, "exit\n", 5);
			exit_err(cmd->args->token, 1);
			exit(255);
		}
		write(2, "exit\n", 5);
		exit(nb % 256);
	}
	write(2, "exit\n", 5);
	return (exit(0), 1);
}

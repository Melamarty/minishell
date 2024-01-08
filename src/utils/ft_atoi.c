/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:37:00 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/08 11:02:46 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	func(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f');
}

static int	func0(const char	*s, int i, int neg)
{
	unsigned long long	res;
	int					digitnbr;

	res = 0;
	digitnbr = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		digitnbr++;
		if (digitnbr == 20)
		{
			if (neg == -1)
				return (0);
			else
				return (-1);
		}
		res = (res * 10) + (s[i++] - '0');
	}
	if (res > LONG_MAX) 
	{
		if (neg == -1)
			return (0);
		else
			return (-1);
	}
	return (((int) res) * neg);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	while (s[i] && (s[i] == ' ' || func(s[i]))) 
		i++;
	if (s[i] == '+' || s[i] == '-') 
	{
		if (s[i] == '-')
			neg *= -1;
		i++;
	}
	while (s[i] && s[i] == '0')
		i++;
	return (func0(s, i, neg));
}
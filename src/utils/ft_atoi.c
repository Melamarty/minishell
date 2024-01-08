/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:37:00 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/08 11:40:01 by mozennou         ###   ########.fr       */
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

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*pp;

	if (!s && !d)
		return (NULL);
	i = 0;
	p = (unsigned char *)d;
	pp = (unsigned char *)s;
	while (i < n)
	{
		p[i] = pp[i];
		i++;
	}
	return (d);
}
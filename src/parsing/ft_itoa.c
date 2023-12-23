#include "parsing.h"

static int	func(int n, int *neg)
{
	int				l;
	unsigned int	k;

	l = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		(*neg) = 1;
		n = -n;
		l++;
	}
	k = n;
	while (k >= 1)
	{
		l++;
		k = k / 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				neg;
	unsigned int	k;
	int				ln;

	neg = 0;
	ln = func(n, &neg);
	if (neg == 1)
		n *= -1;
	k = n;
	res = (char *)malloc(ln + 1);
	if (res == NULL)
		return (NULL);
	if (neg)
		res[0] = '-';
	res[ln] = '\0';
	if (k == 0)
		res[0] = '0';
	while (k != 0)
	{
		res[ln-- - 1] = k % 10 + '0';
		k = k / 10;
	}
	return (res);
}
#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen((char *)s);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (++i < len)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *a, char const *b)
{
	int		i;
	int		a_ln;
	int		b_ln;
	char	*res;

	if (!a && !b)
		return (NULL);
	if (!a)
		return (ft_strdup(b));
	if (!b)
		return (ft_strdup(a));
	a_ln = ft_strlen((char *)a);
	b_ln = ft_strlen((char *)b);
	res = (char *)malloc(a_ln + b_ln + 1);
	if (!res)
		return (res);
	i = -1;
	while (++i < a_ln)
		res[i] = a[i];
	i = -1;
	while (++i < b_ln)
		res[a_ln + i] = b[i];
	res[a_ln + i] = '\0';
	return (res);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

int	putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return ft_strlen(str);
}
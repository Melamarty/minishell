#include "parsing.h"
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
		p[i++] = '\0';
}

void	*ft_calloc(size_t n, size_t s)
{
	void	*res;

	if ((int)n < 0 && (int)s < 0)
		return (NULL);
	res = malloc(n * s);
	if (!res)
		return (NULL);
	ft_bzero(res, s * n);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t ln)
{
	size_t	n;
	size_t	i;
	char	*res;

	n = 0;
	i = -1;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	while (s[start + n] && n < ln)
		n++;
	res = (char *)malloc(n + 1);
	if (res == NULL)
		return (NULL);
	while (++i < n)
		res[i] = s[start + i];
	res[i] = '\0';
	return (res);
}
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

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*pp;

	i = 0;
	p = (unsigned char *)a;
	pp = (unsigned char *)b;
	while (i < n && (p[i] || pp[i]))
	{
		if (p[i] != pp[i])
			return (p[i] - pp[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *a, char *b)
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
	free(a);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}
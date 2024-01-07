#include "../minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while ((str1[i] || str2[i]))
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		my_malloc(0, 1);
		exit(1);
	}
}

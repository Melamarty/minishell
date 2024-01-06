#include "../minishell.h"

int	file_error(char *file)
{
	write(2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	write (2, ": No such file or directory\n", 29);
	return (0);
}

int	put_err(char *file, int flag)
{
	write(2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	if ((ft_strchr(file, '/') && flag) || flag == 33)
		write(2, ": No such file or directory\n", 28);
	else if (flag)
		write(2, ": command not found\n", 20);
	else
		perror(file);
	return (0);
}

int	export_err(char *s)
{
	write (2, "minishell: export: ", 19);
	while (*s)
	{
		write (2, s, 1);
		s++;
	}
	write (2, ": not a valid identifier\n", 25);
	return (1);
}
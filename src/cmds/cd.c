#include "../minishell.h"

int	two_points(char *curr_path,int one)
{
	int		i;
	char	*new_path;

	if (one)
		return (1);
	i = ft_strlen(curr_path) - 2;
	while (curr_path[i] && curr_path[i] != '/')
		i--;
	new_path = malloc(i);
	if (!new_path)
		return (0);
	++i;
	while (--i >= 0)
		new_path[i] = curr_path[i];
	if (chdir(new_path))
	{
		perror("chdir");
		return (1);
	}
	return (0);
}

int	cd(char	*path)
{
	char	*abs_path;
	char	*tmp;

	if (path[0] == '/')
	{
		if (!chdir(path))
			return (1);
		perror("chdir");
		return (0);
	}
	tmp = malloc(1024);
	if (!tmp)
		return (0);
	getcwd(tmp, 1024);
	if (path[0] == '.')
		return (two_points(tmp, path[1] == '\0'));
	free (tmp);
	tmp = ft_strjoin(tmp, "/");
	abs_path = ft_strjoin(tmp, path);
	free (tmp);
	if (!chdir(abs_path))
		return (1);
	perror("chdir");
	free(abs_path);
	return (0);
}
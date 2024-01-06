#include "../minishell.h"

// cc cd.c ../utils/utils1.c pwd.c ../utils/utils.c -lreadline echo.c

int	two_points(char *curr_path, char *path)
{
	int		i;
	char	*new_path;

	if (!path[1] || path[1] == '/')
		return (1);
	i = ft_strlen(curr_path) - 2;
	while (curr_path[i] && curr_path[i] != '/')
		i--;
	new_path = my_malloc(i, 0);
	if (!new_path)
		return (0);
	++i;
	while (--i >= 0)
		new_path[i] = curr_path[i];
	if (chdir(new_path))
		return (1);
	return (0);
}

int	special_path(char *path, t_env *env)
{
	char	*abs_path;
	char	*tmp;

	(void)env;
	tmp = get_env(env, "HOME");
	if (path)
		abs_path = ft_strjoin(tmp, path + 1);
	else
		abs_path = tmp;
	if (!chdir (abs_path))
		return (env->last_exit = 0, 1);
	env->last_exit = 1;
	return (0);
}

int	cd(char *path, t_env *env)
{
	if (!path)
		return (special_path(NULL, env));
	if (path && path[0] == '~')
		return (special_path(path, env));
	if (!chdir(path))
		return (1);
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	env->last_exit = 1;
	return (0);
}

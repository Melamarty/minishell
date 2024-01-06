#include "../minishell.h"

char	*get_env(t_env *envr, char *key)
{
	t_map *env;

	env = envr->env;
	if (!env)
		return (ft_strdup(""));
	while(env && ft_strcmp(env->key, key))
		env = env->next;
	if (!env)
		return ("");
	return (env->val);
}

char **set_env(t_env *env_list)
{
	char **env;
	t_map *tmp;
	int i;

	tmp = env_list->env;
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	env = my_malloc(i * sizeof(char *) + 1, 0);
	i = 0;
	tmp = env_list->env;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		env[i] = ft_strjoin(env[i], tmp->val);
		tmp = tmp->next;
		++i;
	}
	env[i] = NULL;
	return (env);
}

int put_err(char *file, int flag)
{
	write(2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	if ((ft_strchr(file, '/') && flag) || flag == 33)
	{
		write(2, ": No such file or directory\n", 28);
	}
	else if (flag)
		write(2, ": command not found\n", 20);
	else
		perror(file);
	return (0);
}

int exec_system(t_cmd *cmd, t_env *env, char *file) {
    int pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        if (execve(cmd->cmd, cmd->e_args, set_env (env)) == -1) {
			put_err(file, 0);
            exit(126);
        }
    } else {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
			env->last_exit = exit_status;
            return !exit_status;
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            return 128 + signal_number;
        } else {
            return -1;
        }
    }
    return -1;
}


char *locate_cmd(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*ftmp;
	int i;

	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		ftmp = paths[i];
		tmp = ft_strjoin(paths[i], "/");
		ftmp = tmp;
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

int	list_len (t_list *lst)
{
	int len;

	len = 0;
	while (lst)
	{
		++len;
		lst = lst->next;
	}
	return (len);
}

char **set_args(char *file, t_list *args)
{
	char **e_args;
	int		args_len;
	int		i;

	args_len = list_len(args);
	e_args =my_malloc((args_len + 2)* sizeof(char *), 0);
	i = 1;
	e_args[0] = file;
	while (args)
	{
		e_args[i++] = args->token;
		args = args->next;
	}
	e_args[i] = NULL;
	return e_args;
}

int	exec_file(t_cmd *cmd, t_env *env)
{
	char	*file;
	char	*tmp;

	tmp = ft_strdup(cmd->cmd);
	// printf ("tmp is %s\n", tmp);
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
	{
		if (cmd->cmd[0] == '.')
		{
			file = ft_strjoin(getcwd(NULL, 0), cmd->cmd + 1);
			cmd->cmd = file;
		}
		else
			file = cmd->cmd;
		cmd->e_args = set_args(file, cmd->args);
		if (access(cmd->cmd, F_OK) == 0)
			return (exec_system(cmd, env, tmp));
		else
			return (env->last_exit = 127, put_err(tmp, 1));
	}
	file = locate_cmd(cmd->cmd, get_env(env, "PATH"));
	if (! ft_strlen (get_env(env, "PATH")) && access(cmd->cmd, F_OK))
		return (env->last_exit = 127, put_err(tmp, 33));
	if (!file || !ft_strlen(tmp))
		return ( env->last_exit = 127, put_err(tmp, 1));
	cmd->e_args = set_args(file, cmd->args);
	cmd->cmd = ft_strdup (file);
	return (exec_system(cmd, env, tmp));
}

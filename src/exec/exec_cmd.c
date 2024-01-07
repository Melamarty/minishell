#include "../minishell.h"

t_list	*get_wildcard(void)
{
	DIR				*dir;
	t_list			*wild_list;
	struct dirent	*entry;

	wild_list = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1))
			ft_lstadd_back(&wild_list, ft_lstnew(entry->d_name, 0));
		entry = readdir(dir);
	}
	closedir(dir);
	return (wild_list);
}

void	expand_cmd(t_cmd *cmd)
{
	cmd->cmd = cmd->args->token;
	cmd->args = cmd->args->next;
}

t_list	*expand_args(t_list *args, t_env *env)
{
	t_list	*res;
	t_list	*tmp;
	char	*string;
	int		l;

	res = NULL;
	l = 0;
	while(args)
	{
		if (args->expand != 1)
			string = ft_expand(args->token, env);
		else
			string = ft_strdup(args->token);
		if (args->pos && !l && ft_strlen(string))
		{
			ft_lstadd_back(&res, ft_lstnew(string, 0));
			l = 1;
		}
		else if (args->pos && l && ft_strlen(string))
		{
			tmp = ft_lstlast(res);
			tmp->token = ft_strjoin(tmp->token, string);
		}
		else if(ft_strlen(string))
			ft_lstadd_back(&res, ft_lstnew(string, 0));
		args = args->next;
	}
	return (res);
}

int	exec_cmd(t_cmd	*cmd, t_env **envr)
{
	if (!ft_lstlen(cmd->args))
		expand_cmd(cmd);
	else
	{
		cmd->args = expand_args(cmd->args, *envr);
		if (!cmd->args)
			return (0);
		expand_cmd(cmd);
	}
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (echo(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "cd"))
	{
		if (cmd->args)
			return (cd(cmd->args->token, *envr));
		else
			return (cd(NULL, *envr));
	}
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (pwd(cmd, *envr));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (export(cmd, envr));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (unset(envr, cmd->args));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (env(cmd, *envr));
	else if ((ft_strlen(cmd->cmd) && cmd->expand != 1) || cmd->expand != 1)
		return (exec_file(cmd, (*envr)));
	(*envr)->last_exit = 0;
	return (0);
}

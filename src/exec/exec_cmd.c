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

void	expand_cmd(t_cmd *cmd, t_list **args, t_env *env)
{
	t_list	*tmp;

	tmp = *args;
	if (cmd->expand != 1)
		cmd->cmd = ft_expand(cmd->cmd, env);
	while (tmp)
	{
		if (tmp->expand != 1)
			tmp->token = ft_expand(tmp->token, env);
		tmp = tmp->next;
	}
	if (!ft_strlen (cmd->cmd))
	{
		while (cmd->args  && !ft_strlen(cmd->args->token))
			cmd->args = cmd->args->next;
		if (cmd->args)
			cmd->cmd = cmd->args->token;
		if (cmd->args && cmd->args->next)
			cmd->args = cmd->args->next;
		else
			cmd->args = NULL;
	}
}

int	exec_cmd(t_cmd	*cmd, t_env **envr)
{
	// expand_cmd(cmd, &cmd->args, *envr);
	if (!cmd->cmd)
		return (0);
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

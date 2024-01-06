#include "../minishell.h"


t_list *get_wildcard(t_list **_args, t_env **envr)
{
	DIR *dir;
	char tmp[1024];
	t_list *wild_list;
	t_list *args;

	args = *_args;
	wild_list = NULL;
	while (args)
	{
		if (args->token[ft_strlen(args->token) - 1] == '*')
		{
			args->token[ft_strlen(args->token) - 1] = '\0';
			getcwd(tmp, 1024);
			cd(args->token, *envr);
			dir = opendir(".");
			if (!dir)
				return (perror("opendir"), NULL);
			struct dirent *entry;
			while ((entry = readdir(dir)) != NULL)
				if (ft_strncmp(entry->d_name, ".", 1) && ft_strncmp(entry->d_name, "..", 2))
					ft_lstadd_back(&wild_list, ft_lstnew(entry->d_name, 0));
			closedir(dir);
		}
		args = args->next;
	}
	cd(tmp, *envr);
	return (wild_list);
}

void expand_cmd(t_cmd *cmd, t_list **args, t_env *env)
{
	t_list *tmp;

	tmp = *args;
	if (cmd->expand)
		cmd->cmd = ft_expand(cmd->cmd, env);
	while (tmp)
	{
		if (tmp->expand)
			tmp->token = ft_expand(tmp->token, env);
		tmp =tmp->next;
	}
	if (!ft_strlen (cmd->cmd))
	{
		while (cmd->args && !ft_strlen(cmd->args->token))
			cmd->args = cmd->args->next;
		if (cmd->args)
			cmd->cmd = cmd->args->token;
		// if (cmd->args->next)
		// printf ("args next: %s\n", cmd->args->next->token);
		if (cmd->args && cmd->args->next)
			cmd->args = cmd->args->next;
		// else
		// {
		// 	// printf ("enterd\n");
		// 	cmd->args = NULL;
		// 	// cmd->args = cmd->args->next;
		// }
	}
}

void print_lisrt(t_list *list)
{
	while (list)
	{
		printf("%s\n", list->token);
		list = list->next;
	}
}

int	exec_cmd(t_cmd	*cmd, t_env **envr)
{
	expand_cmd(cmd, &cmd->args, *envr);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (echo(cmd, *envr));
	if (!ft_strcmp(cmd->cmd, "cd"))
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
	else if ((ft_strlen(cmd->cmd) && cmd->expand) || !cmd->expand)
		return (exec_file(cmd, (*envr)));
	(*envr)->last_exit = 0;
	return (0);
}
// to do list
// change all paramters to cmd to be able to handle exit status
// modify unset and export to be able to hanle more than one parametre
// test permissions in cd
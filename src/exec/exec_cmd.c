/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:10:10 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/08 11:47:36 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_cmd(t_cmd *cmd)
{
	if (!cmd->args)
	{
		cmd->cmd = NULL;
		return (-1);
	}
	cmd->cmd = cmd->args->token;
	cmd->args = cmd->args->next;
	return (0);
}

void	norm_helper(t_list **res, int *l, char *string)
{
	ft_lstadd_back(res, ft_lstnew(string, 0));
	*l = 1;
}

t_list *ft_lstsplit(char *string, t_list **res)
{
	char	*str;
	char 	**split;
	int		i;

	i = 0;
	split = my_split(string);
	while (split[i])
	{
		str = ft_strdup(split[i]);
		ft_lstadd_back(res, ft_lstnew(str, 0));
		i++;
	}
	return (*res);
}

t_list    *expand_args(t_list *args, t_env *env)
{
    t_list    *res;
    t_list    *tmp;
    char    *string;
    int        l;

    res = NULL;
    l = 0;
    while (args)
    {
        if (args->expand != 1)
        	string = ft_expand(args->token, env);
        else
            string = ft_strdup(args->token);
        if (args->pos == 1 && !l && ft_strlen(string))
            norm_helper(&res, &l, string);
        else if (args->pos && l && ft_strlen(string))
        {
            tmp = ft_lstlast(res);
            tmp->token = ft_strjoin(tmp->token, string);
            if (args->pos == 2)
                l = 0;
        }
        else if (ft_strlen(string))
		{
			if (args->expand)
           		ft_lstadd_back(&res, ft_lstnew(string, 0));
			else
				ft_lstsplit(string, &res);
		}
        args = args->next;
    }
    return (res);
}

int	fix_cmd(t_cmd *cmd, t_env *env)
{
	if (!ft_lstlen(cmd->args))
	{
		if (expand_cmd(cmd))
			return (1);
	}
	else
	{
		cmd->args = expand_args(cmd->args, env);
		if (!cmd->args)
			return (1);
		if (expand_cmd(cmd))
			return (1);
	}
	return (0);
}

int	exec_cmd(t_cmd	*cmd, t_env **envr)
{
	if (fix_cmd(cmd, *envr))
		return ((*envr)->last_exit = 0, 1);
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

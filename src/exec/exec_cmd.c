/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:52:40 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 13:54:48 by mozennou         ###   ########.fr       */
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

void	norm_helper(t_list **res, int *l, char *string, t_list *args)
{
	t_list	*tmp;
	ft_lstadd_back(res, ft_lstnew(string, args->type));
	*l = 1;
	tmp = ft_lstlast(*res);
	tmp->expand = args->expand;
	tmp->type = args->type;
	tmp->fd = args->fd;
}

t_list *ft_lstsplit(char *string, t_list **res, t_list *args)
{
	char	*str;
	t_list	*tmp;
	char 	**split;
	int		i;

	i = 0;
	split = my_split(string);
	while (split[i])
	{
		str = ft_strdup(split[i]);
		ft_lstadd_back(res, ft_lstnew(str, 0));
		tmp = ft_lstlast(*res);
		tmp->expand = args->expand;
		tmp->type = args->type;
		tmp->fd = args->fd;
		i++;
	}
	return (*res);
}

t_list	*wildcard(t_list *args)
{
	t_list	*res;
	t_list	*tmp;
	t_list 	*tmp2;
	
	res = NULL;
	while (args)
	{
		if (ft_strcmp(args->token, "*") || args->expand)
		{
			ft_lstadd_back(&res, ft_lstnew(args->token, 0));
			tmp2 = ft_lstlast(res);
			tmp2->expand = args->expand;
			tmp2->type = args->type;
			tmp2->fd = args->fd;
		}
		else
		{
			tmp2 = get_wildcard();
			if (!res)
				res = tmp2;
			else
			{
				tmp = ft_lstlast(res);
				tmp->next = tmp2;
			}
		}
		args = args->next;
	}
	return (res);
}

t_list    *expand_args(t_list *args, t_env *env, int m)
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
            norm_helper(&res, &l, string, args);
        else if (args->pos && l && ft_strlen(string))
        {
            tmp = ft_lstlast(res);
            tmp->token = ft_strjoin(tmp->token, string);
            if (args->pos == 2)
                l = 0;
        }
        else
        {
            if (args->expand)
                add_cpy(&res, args, args->type, string);
            else
                ft_lstsplit(string, &res, args);
        }
        args = args->next;
    }
	if (!m)
   		return (wildcard(res));
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
		cmd->args = expand_args(cmd->args, env, 0);
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
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (exit_cmd(cmd));
	else if ((ft_strlen(cmd->cmd) && cmd->expand != 1) || cmd->expand != 1)
		return (exec_file(cmd, (*envr)));
	(*envr)->last_exit = 0;
	return (0);
}

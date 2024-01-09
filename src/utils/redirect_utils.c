/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:41:29 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/09 16:13:37 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_redirect(t_cmd *cmd, t_env *env)
{
	if (cmd->redir_in)
		cmd->redir_in = expand_args(cmd->redir_in, env, 1);
	if (cmd->redir_out)
		cmd->redir_out = expand_args(cmd->redir_out, env, 1);
}

int	is_starts(char *str)
{
	while (*str)
	{
		if (*str != '*')
			return (0);
		str++;
	}
	return (1);
}

char	*ft_get_name2(void)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(".expand");
	while (!access(res, F_OK))
	{
		res = ft_strjoin(res, ft_itoa(i));
		i++;
	}
	return (res);
}

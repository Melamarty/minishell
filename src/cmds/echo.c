#include "../minishell.h"

int	echo(t_cmd *cmd, t_env *env)
{
	t_list	*args;
	int		is_n;

	args = cmd->args;
	is_n = 0;
	if (cmd->args && cmd->args->token && !ft_strcmp(cmd->args->token, "-n"))
	{
		is_n = 1;
		args = args->next;
	}
	while (args)
	{
		// if (args->expand != 1)
		// 	ft_putstr_fd(ft_expand(args->token, env), 1);
		// else
			ft_putstr_fd(args->token, 1);
		if (args->next)
			ft_putstr_fd(" ", 1);
		args = args->next;
	}
	if (!is_n)
		write(1, "\n", 1);
	env->last_exit = 0;
	return (1);
}

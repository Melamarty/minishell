#include "../minishell.h"

int unset(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*is_key;

	tmp = cmd->env;
	if (!tmp)
		return (1);
	while (tmp && tmp->key != cmd->args[0])
	{
		is_key = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	tmp = is_key;
	is_key = tmp->next->next;
	free (tmp);
	tmp->next = is_key;
	return (1);
}

#include "../minishell.h"

int	add_back(t_env **env, char *key, char *val)
{
	t_env	*new;
	t_env	*head;

	head = NULL;
	if (*env)
		head = *env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = malloc(ft_strlen(key));
	new->val = malloc(ft_strlen(val));
	new->key = key;
	new->val = val;
	while (*env && (*env)->next)
	{
		printf("====\n");
		(*env) = (*env)->next;
	}
	if (!*env)
	{
		*env = new;
		(*env)->next = NULL;
	}
	else
	{
		(*env)->next = new;
		(*env)->next->next = NULL;
	}
	if (head)
		*env = head;
	return (1);
}

int	is_exist(t_env *env, char *key)
{
	if (!env)
		return (0);
	while (env && ft_strcmp(env->key, key))
		env = env->next;
	if (env)
		return (1);
	return (0);
}

int	export(t_cmd *cmd)
{
	int		i;
	t_env	*new;

	if (is_exist(cmd->env, cmd->args[0]))
	{
		free (cmd->env->key);
		free (cmd->env->val);
		cmd->env->key = cmd->args[0];
		cmd->env->val = cmd->args[1];
		return (1);
	}
	add_back(&cmd->env, cmd->args[0], cmd->args[1]);
	return 0;
}

int	env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		write (1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write (1, env->val, ft_strlen(env->val));
		write(1, "\n", 1);
		env = env->next;
	}
	return (1);
}

int main ()
{
	t_cmd cmd;
	cmd.env = NULL;
	cmd.args = (char **)malloc(2 * sizeof(char *));
	cmd.args[0] = "var1";
	cmd.args[1] = "val1";
	export(&cmd);
	cmd.args[0] = "var2";
	cmd.args[1] = "val2";
	export(&cmd);
	env(cmd.env);
}

#include "../minishell.h"

char	*get_var(t_env *env, char *key, int *i)
{
	if (!env)
		return (" ");
	while(env && ft_strcmp(env->key, key))
		env = env->next;
	if (!env)
		return (" ");
	return (env->val);
}

int	echo(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*var;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = cmd->args[0];
	while (tmp[++i])
	{
		if (tmp[i + 1]  && tmp[i] == '$' && tmp[i + 1] != ' ')
		{
			var = get_var(cmd->env, cmd->args[++j], &i);
			if (!var)
				return (0);
			write(1, var, ft_strlen(var));
			i += ft_strlen(cmd->args[j]);
		}
		else
			write(1, &tmp[i], 1);
	}
	write(1, "\n", 1);
	return (1);
}

int main() {
	t_env env;
	env.key = "USE";
	env.val = "1337";
	env.next = NULL;
    t_cmd cmd;
    cmd.cmd = "echo";
	cmd.args = malloc(2 * sizeof(char *));
	cmd.args[0] = "hello _$USE_ is the user";
	cmd.args[1] = "USE";
    cmd.env = &env;
    echo(&cmd);
    return 0;
}
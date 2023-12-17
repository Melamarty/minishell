#include "parsing.h"

void	bash_loop()
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = readline("\e[1;32mminishell >>✗");
		t_list *tokens = tokenizing(cmd);
		aff_list(tokens);
		t_tree *tree = condition(&tokens);
		//in_out(tokens);
		print_tree(tree, 0);
		free(cmd);
		ft_lstclear(&tokens, free);
	}
}

int main(int ac, char **av, char **env)
{
	t_env *my_env = get_env(env);
	//bash_loop();
	while (my_env)
	{
		printf("%s=%s\n", my_env->key, my_env->val);
		my_env = my_env->next;
	}
}
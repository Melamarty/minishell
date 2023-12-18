#include "parsing.h"

void lol()
{
	system("leaks a.out");
}

void	bash_loop()
{
	t_list *cpy;
	char	*cmd;
	cmd = NULL;
	// while (1)
	// {
		cmd = readline("\e[1;32mminishell >> \e[0m");
		t_list *tokens = tokenizing(cmd);
		if (!tokens)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			// continue ;
			exit(1);
		}
		aff_list(tokens);
		cpy = tokens;
		t_tree *tree = condition(&tokens);
		print_tree(tree, 0);
		tree_free(tree);
		free(cmd);
		ft_lstclear(&cpy, free);
	// }
}

int main(int ac, char **av, char **env)
{
	atexit(lol);
	//t_env *my_env = get_env(env);
	bash_loop();
}
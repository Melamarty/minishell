#include "parsing.h"

void	bash_loop()
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = readline("\e[1;32mminishell >>✗");
		t_list *tokens = tokenizing(cmd);
		//t_tree *tree = condition(&tokens);
		//in_out(tokens);
		aff_list(tokens);
		//print_tree(tree, 0);
		free(cmd);
		ft_lstclear(&tokens, free);
	}
}


int main ()
{
	bash_loop();
}
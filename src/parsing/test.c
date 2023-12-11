#include "../minishell.h"

void aff_list(t_list *lst)
{
	printf("\nTokens : ");
	while (lst)
	{
		printf("%s --> ", lst->token);
		lst = lst->next;
	}
	printf("\n\n");
}

void	bash_loop()
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = readline("\e[1;32mminishell >>✗");
		t_list *tokens = get_tokens(cmd);
		aff_list(tokens);
		// if (!ft_strncmp(cmd, "exit", 4))
		// 	break;
		write (1, "\e[1;34m", 7);
		//handel_cmd(cmd);
		ft_lstclear(&tokens, free);
	}
}

int main ()
{
	bash_loop();
}
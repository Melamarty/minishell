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
	while (1)
	{
		cmd = readline("\e[1;32mminishell >> \e[0m");
		if (!cmd)
			exit(0);
		add_history(cmd);
		t_list *tokens = tokenizing(cmd);
		if (!tokens)
			continue ;
		aff_list(tokens);
		cpy = tokens;
		t_tree *tree = condition(&tokens);
		print_tree(tree, 0);
		tree_free(tree);
		free(cmd);
		ft_lstclear(&cpy, free);
	}
}

int main(int ac, char **av, char **env)
{
	//atexit(lol);
	//t_env *my_env = get_env(env);
	bash_loop();
}


// t_list	*ft_lstcpy(t_list *lst)
// {
// 	t_list	*res = NULL;

// 	res = ft_lstnew(ft_strdup(lst->token), lst->type);
// 	res->expand = lst->expand;
// 	res->pos = lst->pos;
// 	return (res);
// }

// t_list	*flip(t_list *lst)
// {
// 	t_list	*res = NULL;
// 	t_list	*p;
// 	int		i = ft_lstsize(lst);
// 	int		j = 0;

// 	while(i)
// 	{
// 		j = -1;
// 		p = lst;
// 		while (++j < i - 1)
// 			p = p->next;
// 		ft_lstadd_back(&res, ft_lstcpy(p));
// 		i--;
// 	}
// 	p = res;
// 	while (p)
// 	{
// 		if (p->type == TOKEN_BRKT_OPEN)
// 		{
// 			free(p->token);
// 			p->token = ft_strdup(")");
// 			p->type = TOKEN_BRKT_CLOSE;
// 		}
// 		else if (p->type == TOKEN_BRKT_CLOSE)
// 		{
// 			free(p->token);
// 			p->token = ft_strdup("(");
// 			p->type = TOKEN_BRKT_OPEN;
// 		}
// 		p = p->next;
// 	}
// 	return (res);
// }
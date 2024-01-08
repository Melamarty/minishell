#include "minishell.h"

int sig;

void aff_list(t_list *lst)
{
	while (lst) //////////////////////////////////////////////////////////////////////
	{
		printf("%s -(%d)(%d)-> ", lst->token, lst->expand, lst->pos);
		lst = lst->next;
	}
	printf("\n\n");
}

void sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	// write(1, "\e[1;32", 7);
	rl_replace_line("", 0);
	rl_redisplay();
	sig = 1;
}


void	bash_loop(t_env *my_env)
{
	t_list *cpy;
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		sig = 0;
		signal(SIGINT, sigint_handler);
		write (1, "\e[1;32m", 7);
		rl_catch_signals = 0;
		cmd = readline("\e[1;32mminishell >> \e[0m");
		add_history(cmd);
		if (!cmd || !ft_strncmp(cmd, "exit", 4)) // to handel espace
			return (my_malloc(0, 1), free (cmd), (void )printf("exit\n"));
		t_list *tokens = tokenizing(cmd, my_env);
		//aff_list(tokens);
		free(cmd);
		if (!tokens)
			continue ;
		if (sig)
			my_env->last_exit = 1;
		cpy = tokens;
		t_tree *tree = condition(ft_lstlast(tokens));
		//print_tree(tree, 0);
		// printf ("\e[1;31mexecuting\e[0m\n");
		exec_line(&tree, &my_env);
		// printf ("last exit status is %d\n", my_env->last_exit);
	}
}

void f(void)
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
	t_list *lst;
	char	*tmp;

	(void)ac;
	(void)av;
	// atexit(f);
	t_env *enver = my_malloc(sizeof(t_env), 0);
	t_map *my_env = get_env55(env);
	enver->env = my_env;
	enver->ex_env = NULL;
	if (!is_exist(enver->env, "SHLVL"))
		env_add_back(&enver->env, "SHLVL", "1");
	else
	{
		lst = my_malloc(sizeof(t_list), 0);
		lst->token = ft_strdup("SHLVL");
		lst->next = NULL;
		tmp = ft_itoa (ft_atoi(get_env(enver, "SHLVL")) + 1);
		unset(&enver, lst);
		env_add_back(&enver->env, "SHLVL", tmp);
	}
	bash_loop(enver);
	// while (1)
	// 	pause();
	return (0);
}

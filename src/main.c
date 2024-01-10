/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:17:15 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 21:16:45 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT && g_sig >= 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 1;
	}
	else if (sig == SIGINT)
		g_sig = -2;
	else if (sig == SIGQUIT)
		g_sig = -3;
}

void	setup_signals(t_env *my_env)
{
	if (g_sig == -2)
		my_env->last_exit = 130;
	else if (g_sig == -3)
		my_env->last_exit = 131;
	g_sig = 0;
	signal(SIGINT, sigint_handler);
	rl_catch_signals = 0;
	signal(SIGQUIT, sigint_handler);
}

void	bash_loop(t_env *my_env)
{
	t_list	*cpy;
	char	*cmd;
	t_list	*tokens;
	t_tree	*tree;

	cmd = NULL;
	while (1)
	{
		setup_signals(my_env);
		cmd = readline("\e[1;32mminishell >> \e[0m");
		add_history(cmd);
		if (!cmd)
			return (my_malloc(0, 1), exit (0));
		tokens = tokenizing(cmd, my_env);
		free(cmd);
		if (!tokens)
			continue ;
		cpy = tokens;
		tree = condition(ft_lstlast(tokens));
		if (g_sig)
			my_env->last_exit = 1;
		exec_line(&tree, &my_env);
		my_open(NULL, 0, 0, 1);
	}
}

t_env	*setup_env(char **env)
{
	t_list	*lst;
	int		tmp;
	t_env	*enver;
	t_map	*my_env;

	enver = my_malloc(sizeof(t_env), 0);
	my_env = get_env55(env);
	enver->env = my_env;
	enver->ex_env = NULL;
	lst = my_malloc(sizeof(t_list), 0);
	if (!is_exist(enver->env, "SHLVL"))
		env_add_back(&enver->env, "SHLVL", "1");
	else
	{
		lst->token = ft_strdup("SHLVL");
		lst->next = NULL;
		tmp = ft_atoi(get_env(enver, "SHLVL")) + 1;
		if (tmp < 0)
			tmp = 0;
		unset(&enver, lst);
		env_add_back(&enver->env, "SHLVL", ft_itoa (tmp));
	}
	lst->token = ft_strdup("OLDPWD");
	unset (&enver, lst);
	return (enver);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envr;

	(void)ac;
	(void)av;
	envr = setup_env (env);
	envr->last_exit = 0;
	bash_loop(envr);
	return (0);
}

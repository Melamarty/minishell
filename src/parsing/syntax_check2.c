/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:13:27 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 21:12:23 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	func(t_list **cpy, t_list *pp, t_env *env)
{
	char	*string;

	if (is_valid2(pp, (*cpy), 0))
	{
		ft_putsyntax_error(env);
		return (1);
	}
	if (pp && pp->type == TOKEN_HEREDOC && (*cpy)->type == TOKEN_EXPR)
	{
		string = ft_strdup((*cpy)->token);
		while ((*cpy)->next && (*cpy)->next->pos)
		{
			string = ft_strjoin(string, (*cpy)->next->token);
			(*cpy) = (*cpy)->next;
			if ((*cpy)->pos == 2)
				break ;
		}
		(*cpy)->fd = read_heredoc(string, env);
		if ((*cpy)->fd == -1)
			return (1);
	}
	return (0);
}

t_list	*syntax_check(t_list *p, t_env *env)
{
	t_list	*cpy;
	t_list	*pp;
	int		f;

	cpy = p;
	pp = NULL;
	f = 0;
	while (cpy)
	{
		cpy->fd = -1;
		if (cpy->type == TOKEN_BRKT_OPEN)
			f++;
		else if (cpy->type == TOKEN_BRKT_CLOSE)
			f--;
		if (f < 0)
			return (ft_putsyntax_error(env));
		if (func(&cpy, pp, env))
			return (NULL);
		pp = cpy;
		cpy = cpy->next;
	}
	if (is_valid2(pp, NULL, f))
		return (ft_putsyntax_error(env));
	return (relink(p, env));
}

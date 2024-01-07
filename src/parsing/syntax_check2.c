/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:14:41 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/07 17:46:11 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	func(t_list *cpy, t_list *pp, t_list *p, t_env *env)
{
	(void)p;
	if (is_valid2(pp, cpy, 0))
	{
		ft_putsyntax_error(NULL);
		return (1);
	}
	if (pp && pp->type == TOKEN_HEREDOC && cpy->type == TOKEN_EXPR)
	{
		my_close(cpy);
		cpy->fd = read_heredoc(cpy->token, env);
		if (cpy->fd == -1)
		{
			return (1);
		}
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
		if (f < 0 || ft_strchr(cpy->token, ';') || ft_strchr(cpy->token, '\\'))
			return (ft_putsyntax_error(NULL));
		if (func(cpy, pp, p, env))
			return (NULL);
		pp = cpy;
		cpy = cpy->next;
	}
	if (is_valid2(pp, NULL, f))
		return (ft_putsyntax_error(NULL));
	return (relink(p));
}

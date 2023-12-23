/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:44:22 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/23 13:25:42 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	func(t_list *cpy, t_list *pp, t_list *p)
{
	if (is_valid(pp, cpy, 0))
	{
		ft_lstclear(&p, free);
		ft_putsyntax_error(NULL);
		return (1);
	}
	if (pp && pp->type == TOKEN_HEREDOC && cpy->type == TOKEN_EXPR)
	{
		cpy->fd = read_heredoc(cpy->token);
		if (cpy->fd == -1)
		{
			ft_lstclear(&p, free);
			return (1);
		}
	}
	return (0);
}

t_list	*syntax_check(t_list *p)
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
		if (f < 0 || ft_strchr(cpy->token, ';'))
			return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
		if (func(cpy, pp, p))
			return (NULL);
		pp = cpy;
		cpy = cpy->next;
	}
	if (is_valid(pp, NULL, f))
		return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
	return (relink(p));
}

int	is_hight(int type)
{
	if (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE)
		return (1);
	else if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN)
		return (2);
	return (0);
}

static	int	func1(t_list **tk, t_list **p, t_list **pp, int flg)
{
	if (flg == 0)
	{
		ft_lstadd_back(p, ft_lstnew(ft_strdup((*tk)->token), TOKEN_EXPR));
		*pp = ft_lstlast(*p);
		(*pp)->expand = (*tk)->expand;
		return (1);
	}
	else if (p)
	{
		(*pp) = ft_lstlast(*p);
		(*pp)->token = ft_strjoin((*pp)->token, (*tk)->token);
	}
	return (flg);
}

static int	func2(t_list *tk, t_list **p, t_list **pp)
{
	ft_lstadd_back(p, ft_lstnew(ft_strdup(tk->token), tk->type));
	(*pp) = ft_lstlast(*p);
	(*pp)->expand = tk->expand;
	(*pp)->pos = tk->pos;
	return (0);
}

t_list	*out_of_quotes(t_list	*tk)
{
	t_list	*p;
	t_list	*pp;
	t_list	*l;
	char	*s;
	int		flg;

	p = NULL;
	s = NULL;
	flg = 0;
	l = tk;
	while (tk)
	{
		if (tk->type == TOKEN_SPACE)
			flg = 0;
		if (tk->pos == 0 && tk->type != TOKEN_D_Q
			&& tk->type != TOKEN_S_Q && tk->type != TOKEN_SPACE)
			flg = func2(tk, &p, &pp);
		else if (tk->type != TOKEN_D_Q && tk->type != TOKEN_S_Q
			&& tk->type != TOKEN_SPACE)
			flg = func1(&tk, &p, &pp, flg);
		tk = tk->next;
	}
	ft_lstclear(&l, free);
	return (syntax_check(p));
}

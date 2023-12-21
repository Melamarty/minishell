/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:45:56 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/21 21:34:46 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_expr(char *s)
{
	char	*res;
	int		l;

	l = 0;
	while (s[l] && !is_special(s + l))
		l++;
	res = malloc(l + 1);
	l = 0;
	while (s[l] && !is_special(s + l))
	{
		res[l] = s[l];
		l++;
	}
	res[l] = 0;
	return (res);
}

// static void func2(int flg, t_list **tokens, char *expr, int *i, int inquotes)
// {
// 	int	l

// 	l = is_special(expr + i);
// 	if (l)
// 	{
// 		if (l == TOKEN_SPACE)
// 		{
// 			i++;
// 			flg = 1;
// 			return ;
// 		}
// 		flg = set_space(tokens, flg);
// 		ft_lstadd_back(tokens, ft_lstnew(ft_get_special(l), l));
// 		inquotes = func(inquotes, *i, tokens, expr);
// 	}
// 	else
// 	{
// 		flg = set_space(tokens, flg);
// 		ft_lstadd_back(tokens, ft_lstnew(ft_get_expr(expr + *i), TOKEN_EXPR));
// 	}
// 	(*i) += ft_strlen(ft_lstlast(*tokens)->token);
// }

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

int is_hight(int type)
{
	if (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE || type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

static	int	func3(int type1, int type2)
{
	if (type2 == TOKEN_BRKT_OPEN && type1 == TOKEN_BRKT_CLOSE)
		return (type2);
	if (type1 == TOKEN_BRKT_OPEN && type2 == TOKEN_BRKT_CLOSE)
		return (type1);
	if (type1 == TOKEN_BRKT_CLOSE && (is_hight(type2)))
		return (type1);
	if (type2 == TOKEN_BRKT_CLOSE && type1 == TOKEN_EXPR)
		return (type2);
	if (type2 == TOKEN_BRKT_OPEN && (is_hight(type1)))
		return (type2);
	if (type1 == TOKEN_BRKT_OPEN && type2 == TOKEN_EXPR)
		return (type1);
	if (type2 == TOKEN_HEREDOC && type1 == TOKEN_HEREDOC)
		return (type1);
	if (type2 == TOKEN_REDIR_APPEND && type1 == TOKEN_REDIR_APPEND)
		return (type1);
	if (type2 == TOKEN_REDIR_IN && type1 == TOKEN_REDIR_IN)
		return (type1);
	if (type2 == TOKEN_REDIR_OUT && type1 == TOKEN_REDIR_OUT)
		return (type1);
	if (type2 == TOKEN_PIPE && type1 == TOKEN_PIPE)
		return (type1);
	if (type2 == TOKEN_OR && type1 == TOKEN_OR)
		return (type1);
	if (type2 == TOKEN_AND && type1 == TOKEN_AND)
		return (type1);
	if (type2 == TOKEN_REDIR_IN && type1 == TOKEN_REDIR_IN)
		return (type1);
	if (type1 == TOKEN_EXPR || type2 == TOKEN_EXPR)
		return (0);
	if (type1 == TOKEN_BRKT_CLOSE || type2 == TOKEN_BRKT_CLOSE)
		return (0);
	if (type1 == TOKEN_BRKT_OPEN || type2 == TOKEN_BRKT_OPEN)
		return (0);
	if (type1 != type2)
		return (type1);
	return (0);
}

static int	func4(int l)
{
	if (l == TOKEN_AND || l == TOKEN_OR || l == TOKEN_PIPE || l == TOKEN_HEREDOC
		|| l == TOKEN_REDIR_APPEND || l == TOKEN_REDIR_OUT || 
		l == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

static int	func6(int l)
{
	if (l == TOKEN_AND || l == TOKEN_OR || l == TOKEN_PIPE)
		return (1);
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
		if (tk->pos == 0 && tk->type != TOKEN_D_Q && tk->type != TOKEN_S_Q && tk->type != TOKEN_SPACE)
		{
			ft_lstadd_back(&p, ft_lstnew(ft_strdup(tk->token), tk->type));
			pp = ft_lstlast(p);
			pp->expand = tk->expand;
			pp->pos = tk->pos;
			flg = 0;
		}
		else if(tk->type != TOKEN_D_Q && tk->type != TOKEN_S_Q  && tk->type != TOKEN_SPACE)
			flg = func1(&tk, &p, &pp, flg);
		tk = tk->next;
	}
	ft_lstclear(&l, free);
	return (syntax_check(p));
}

static int valid(char *s)
{
	int	i;

	i = 0;
	if (!ft_strchr(s, '$'))
		return (0);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

t_list	*tokenizing(char *expr)
{
	t_list	*tokens;
	t_list	*p;
	int		in;

	tokens = get_tokens(expr);
	if (!tokens)
		return (NULL);
	in = 0;
	p = tokens;
	while (p)
	{
		if (p->type == TOKEN_S_Q)
		{
			if(!in)
				in = 1;
			else
				in = 0;
		}
		if (p->type == TOKEN_EXPR && valid(p->token) && !in)
			p->expand = 1;
		else
			p->expand = 0;
		p = p->next;
	}
	in_out(tokens);
	return (out_of_quotes(tokens));
}

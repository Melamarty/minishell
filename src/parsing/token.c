#include "parsing.h"

int	is_special(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (TOKEN_OR);
	else if (!ft_strncmp(s, "&&", 2))
		return (TOKEN_AND);
	else if (*s == '&')
		return (-1);
	else if (!ft_strncmp(s, ">>", 2))
		return (TOKEN_REDIR_APPEND);
	else if (!ft_strncmp(s, "<<", 2))
		return (TOKEN_HEREDOC);
	else if (*s == '|')
		return (TOKEN_PIPE);
	else if (*s == '(')
		return (TOKEN_BRKT_OPEN);
	else if (*s == ')')
		return (TOKEN_BRKT_CLOSE);
	else if (*s == '<')
		return (TOKEN_REDIR_IN);
	else if (*s == '>')
		return (TOKEN_REDIR_OUT);
	else if (*s == '\"')
		return (TOKEN_D_Q);
	else if (*s == '\'')
		return (TOKEN_S_Q);
	else if (*s == ' ' || *s == '\t')
		return (TOKEN_SPACE);
	return (TOKEN_EXPR);
}

char *ft_get_special(int l)
{
	if (l == TOKEN_OR)
		return (ft_strdup("||"));
	else if (l == TOKEN_AND)
		return (ft_strdup("&&"));
	else if (l == TOKEN_REDIR_APPEND)
		return (ft_strdup(">>"));
	else if (l == TOKEN_HEREDOC)
		return (ft_strdup("<<"));
	else if (l == TOKEN_PIPE)
		return (ft_strdup("|"));
	else if (l == TOKEN_BRKT_OPEN)
		return (ft_strdup("("));
	else if (l == TOKEN_BRKT_CLOSE)
		return (ft_strdup(")"));
	else if (l == TOKEN_REDIR_IN)
		return (ft_strdup("<"));
	else if (l == TOKEN_REDIR_OUT)
		return (ft_strdup(">"));
	else if (l == TOKEN_D_Q)
		return (ft_strdup("\""));
	else if (l == TOKEN_S_Q)
		return (ft_strdup("\'"));
	else if (l == TOKEN_SPACE)
		return (ft_strdup(" "));
	return (NULL);
}

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

char	*get_arg(char *s, int l)
{
	int		i;
	char	*res;
	char	c;

	i = 0;
	if (l == TOKEN_D_Q)
		c = '\"';
	else
		c = '\'';
	while (s[i] && s[i] != c)
		i++;
	res = malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	if (s[i] == '\0')
		return (NULL);
	res[i] = 0;
	return (res);
}

static int	func(int inquotes, int *i, t_list **tokens, char *expr)
{
	int		l;
	char	*arg;

	l = is_special(expr + *i);
	if ((l == TOKEN_D_Q || l == TOKEN_S_Q) && !inquotes)
	{
		(*i)++;
		arg = get_arg(expr + (*i), l);
		if (!arg)
			return (-1);
		ft_lstadd_back(tokens, ft_lstnew(get_arg(expr + (*i), l),TOKEN_EXPR));
		return (1);
	}
	return (0);
}	

int set_space(t_list **tokens, int flg)
{
	if (flg)
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(" "),TOKEN_SPACE));
	return (0);
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

static int	func5(char *s, int l, int *i, int *flg)
{
	if (l == TOKEN_SPACE)
	{
		*flg = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

t_list	*get_tokens(char *expr)
{
	t_list	*tokens;
	int		flg;
	int		inquotes;
	int		i;
	int		l;

	i = 0;
	flg = 0;
	inquotes = 0;
	tokens = NULL;
	while (expr[i])
	{
		l = is_special(expr + i);
		if (l == -1)
			return (ft_lstclear(&tokens, free), ft_putsyntax_error(NULL));
		if (l)
		{
			if (func5(expr, l, &i, &flg))
				continue ;
			flg = set_space(&tokens, flg);
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_special(l), l));
			inquotes = func(inquotes, &i, &tokens, expr);
			if (inquotes == -1)
				return (ft_lstclear(&tokens, free), ft_putsyntax_error(NULL));
		}
		else
		{
			flg = set_space(&tokens, flg);
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_expr(expr + i), TOKEN_EXPR));
		}
		i += ft_strlen(ft_lstlast(tokens)->token);
	}
	return (tokens);
}

void	in_out(t_list *tokens)
{
	t_list	*p;
	t_list	*pp;
	int	inquotes;

	inquotes = 0;
	p = tokens;
	pp = NULL;
	while (p)
	{
		if (p->type == TOKEN_EXPR)
		{
			if (p->next && (p->next->type == TOKEN_D_Q || p->next->type == TOKEN_S_Q))
				p->pos = 1;
			else if (pp && (pp->type == TOKEN_D_Q || pp->type == TOKEN_S_Q))
				p->pos = 1;
			else
				p->pos = 0;
		}
		else
			p->pos = 0;
		pp = p;
		p = p->next;
	}
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
		return (type2);
	if (type2 == TOKEN_BRKT_OPEN && (is_hight(type1)))
		return (type2);
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

int	is_valid(t_list *a, t_list *b, int f)
{
	int	l;

	if (f)
		return (1);
	if (!a)
	{
		if (func6(b->type))
			return (1);
	}
	else if(!b)
	{
		if (func4(a->type))
			return (1);
	}
	else
	{
		l = func3(b->type, a->type);
		if (l)
			return (1);
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
		if(cpy->type == TOKEN_BRKT_OPEN)
			f++;
		else if (cpy->type == TOKEN_BRKT_CLOSE)
			f--;
		if (is_valid(pp, cpy, 0))
			return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
		pp = cpy;
		cpy = cpy->next;
	}
	if (is_valid(pp, NULL, f))
		return (ft_lstclear(&p, free), ft_putsyntax_error(NULL));
	return (p);
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
		// if (tk->next && ((tk->type == TOKEN_D_Q && tk->next->type == TOKEN_D_Q)
		// 	|| (tk->type == TOKEN_S_Q && tk->next->type == TOKEN_S_Q)))
		// {
		// 	ft_lstadd_back(&p, ft_lstnew(ft_strdup(""), TOKEN_EXPR));
		// 	tk=tk->next;
		// }
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

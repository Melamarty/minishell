#include "parsing.h"
#include <string.h>


int	is_special(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (TOKEN_OR);
	else if (!ft_strncmp(s, "&&", 2))
		return (TOKEN_AND);
	else if (!ft_strncmp(s, ">>", 2))
		return (TOKEN_REDIR_APPEND);
	else if (!ft_strncmp(s, "<<", 2))
		return (TOKEN_HEREDOC);
	else if (*s == '|')
		return (TOKEN_PIPE);
	else if (*s == '(')
		return (TOKEN_BRACKET_OPEN);
	else if (*s == ')')
		return (TOKEN_BRACKET_CLOSE);
	else if (*s == '<')
		return (TOKEN_REDIR_IN);
	else if (*s == '>')
		return (TOKEN_REDIR_OUT);
	else if (*s == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	else if (*s == '\'')
		return (TOKEN_SINGLE_QUOTE);
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
	else if (l == TOKEN_BRACKET_OPEN)
		return (ft_strdup("("));
	else if (l == TOKEN_BRACKET_CLOSE)
		return (ft_strdup(")"));
	else if (l == TOKEN_REDIR_IN)
		return (ft_strdup("<"));
	else if (l == TOKEN_REDIR_OUT)
		return (ft_strdup(">"));
	else if (l == TOKEN_DOUBLE_QUOTE)
		return (ft_strdup("\""));
	else if (l == TOKEN_SINGLE_QUOTE)
		return (ft_strdup("\'"));
	else if (l == TOKEN_SPACE)
		return (ft_strdup(" "));
	return (ft_strdup("EXPR"));
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
	if (l == TOKEN_DOUBLE_QUOTE)
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
	res[i] = 0;
	return (res);
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
		if (l)
		{
			if (l == TOKEN_SPACE)
			{
				i++;
				flg = 1;
				continue ;
			}
			if (flg)
			{
				ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(" "),TOKEN_SPACE));
				flg = 0;
			}
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_special(l), l));
			if (l == TOKEN_DOUBLE_QUOTE || l == TOKEN_SINGLE_QUOTE)
			{
				if (!inquotes)
				{
					i++;
					ft_lstadd_back(&tokens, ft_lstnew(get_arg(expr + i, l),TOKEN_EXPR));
					inquotes = 1;
				}
				else
					inquotes = 0;
			}
		}
		else
		{
			if (flg)
			{
				ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(" "), TOKEN_SPACE));
				flg = 0;
			}
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_expr(expr + i), TOKEN_EXPR));
		}
		i += ft_strlen(ft_lstlast(tokens)->token);
	}
	return (tokens);
}

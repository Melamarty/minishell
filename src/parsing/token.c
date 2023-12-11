#include "../minishell.h"

t_list	*get_tokens(char *expr)
{
	t_list	*tokens;
	int		inquote;
	int		i;
	int		j;

	tokens = NULL;
	inquote = 0;
	i = 0;
	j = 0;
	while (expr[i])
	{
		while(expr[i] && (expr[i] == ' ' || expr[i] == '\t'))
			i++;
		if (expr[i])
			j = i;
		if (expr[i] && (expr[i] == '\"' || expr[i] == '\''))
		{
			if (expr[i] == '\"' )
				inquote = 1;
			else
				inquote = 2;
			i++;
			j++;
		}
		if (inquote)
		{
			if (inquote == 1)
			{
				while (expr[i] && expr[i] != '\"')
					i++;
			}
			else if (inquote == 2)
			{
				while (expr[i] && expr[i] != '\'')
					i++;
			}
			inquote = 0;
		}
		if (expr[i] == '\0')
			return (ft_lstclear(&tokens, free), NULL);
		else
		{
			while (expr[i] && expr[i] != ' ' && expr[i] != '\t')
				i++;
		}
		if (expr[j] && ft_lstadd_back(&tokens, ft_lstnew(ft_substr(expr, j, i - j))))
			return (ft_lstclear(&tokens, free), exit(1), NULL);
		while(expr[i] && (expr[i] == ' ' || expr[i] == '\t'))
			i++;
	}
	return (tokens);
}

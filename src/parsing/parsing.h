#ifndef PARSING_H
# define PARSING_H

#include "../minishell.h"

enum
{
	TOKEN_EXPR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SPACE,
	TOKEN_BRACKET_OPEN,
	TOKEN_BRACKET_CLOSE,
	TOKEN_D_Q,
	TOKEN_S_Q,
	TOKEN_END
} ;


t_list	*get_tokens(char *expr);
t_list	*ft_lstnew(char *content, int type);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*ft_substr(char const *s, unsigned int start, size_t ln);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *a, const char *b, size_t n);
t_list	*ft_lstlast(t_list *lst);
t_tree	*pipeline(t_list **tokens);
t_tree 	*new_node(t_cmd *cmd, int type);
void	add_node(t_tree **tree, t_cmd *cmd, int	left);
t_tree	*condition(t_list **tokens);
char	*ft_strjoin(char *a, char *b);
t_list	*tokenizing(char *expr);
char	*ft_strchr(const char *s, int c);
t_env	*get_env(char **env);
void	print_tree(t_tree	*tree, int c);     /////////////////////////
void	in_out(t_list *tokens); ///////////
void aff_list(t_list *lst); ///////////

#endif

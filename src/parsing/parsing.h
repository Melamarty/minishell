#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

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
	TOKEN_BRKT_OPEN,
	TOKEN_BRKT_CLOSE,
	TOKEN_D_Q,
	TOKEN_S_Q,
} ;

t_list	*get_tokens(char *expr);
t_list	*ft_lstnew(char *content, int type);
int		ft_lstsize(t_list *lst);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*ft_substr(char const *s, unsigned int start, size_t ln);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *a, const char *b, size_t n);
t_list	*ft_lstlast(t_list *lst);
t_tree	*pipeline(t_list *tokens);
t_tree	*new_node(t_cmd *cmd, int type);
void	add_node(t_tree **tree, t_cmd *cmd, int left);
t_tree 	*condition(t_list *tokens);
char	*ft_strjoin(char *a, char *b);
t_list	*tokenizing(char *expr);
char	*ft_strchr(const char *s, int c);
t_map	*get_env(char **env);
void	ft_putstr_fd(char *s, int fd);
void	tree_free(t_tree *tree);
void	*ft_putsyntax_error(char *s);
t_map	*ft_envlast(t_map *env);
char	*get_arg(char *s, int l);
int		is_special(char *s);
int		set_space(t_list **tokens, int flg);
char	*ft_get_expr(char *s);
t_list	*syntax_check(t_list *p);
int		is_valid(t_list *a, t_list *b, int f);
t_list	*in_out(t_list *tokens);
t_list	*relink(t_list *p);
int		is_hight(int type);
t_list	*out_of_quotes(t_list	*tk);
void	print_tree(t_tree	*tree, int c);     /////////////////////////
void aff_list(t_list *lst); ///////////

#endif

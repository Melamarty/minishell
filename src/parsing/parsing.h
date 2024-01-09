/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:11:24 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 15:23:38 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_list	*get_tokens(char *expr, int i, t_env *env);
t_list	*ft_lstnew(char *content, int type);
int		ft_lstsize(t_list *lst);
int		ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		func333(int l, int *i, int *flg, t_list **tokens);
int		my_close(t_list *cpy);
t_tree	*pipeline(t_list *tokens);
t_tree	*new_node(t_cmd *cmd, int type);
t_tree	*condition(t_list *tokens);
t_list	*tokenizing(char *expr, t_env *env);
char	*ft_strchr(const char *s, int c);
t_map	*get_env55(char **env);
t_map	*ft_envnew(char *key, char *val);
void	ft_putstr_fd(char *s, int fd);
void	*ft_putsyntax_error(t_env *env);
t_map	*ft_envlast(t_map *env);
char	*get_arg(char *s, int l);
t_tree	*command(t_list *tokens);
char	*ft_get_special(int l);
int		is_special(char *s);
int		set_space(t_list **tokens, int flg);
char	*ft_get_expr(char *s);
t_list	*syntax_check(t_list *p, t_env *env);
int		is_valid2(t_list *a, t_list *b, int f);
t_list	*in_out(t_list *tokens);
t_list	*relink(t_list *p, t_env *env);
t_tree	*command(t_list *tokens);
void	redir_add(t_list **lst, char *token, int type);
int		set_cmd(t_cmd **cmd);
int		level(t_list *tk);
int		is_hight(int type);
t_list	*mark_token2(t_list *tokens, t_list **cpy);
t_list	*out_of_quotes(t_list	*tk, t_env *env);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
int		read_heredoc(char *limiter, t_env *env);
#endif

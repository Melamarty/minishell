/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:22:35 by mel-amar          #+#    #+#             */
/*   Updated: 2024/01/10 21:03:02 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>

typedef struct s_map
{
	char			*key;
	char			*val;
	struct s_map	*next;
}	t_map;

typedef struct _s_env
{
	t_map	*env;
	t_map	*ex_env;
	int		last_exit;
}	t_env;

typedef struct s_list
{
	char			*token;
	int				type;
	int				pos;
	int				expand;
	int				visited;
	int				fd;
	struct s_list	*last;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	t_list			*args;
	char			**e_args;
	t_list			*redir_in;
	t_list			*redir_out;
	int				expand;
	int				flag;
}	t_cmd;

typedef struct s_tree
{
	t_cmd			*cmd;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_adress
{
	void			*addr;
	int				fd;
	struct s_adress	*next;
}	t_adress;

// signal variable
int			g_sig;

/////////////////////////////////
int			ft_strcmp(char *str1, char *str2);
int			ft_strncmp(char *str1, char *str2, int n);

// cmds
int			echo(t_cmd *cmd, t_env *env);
int			cd(t_cmd *cmd, t_env *env);
char		*get_env(t_env *env, char *key);
int			pwd(t_cmd *cmd, t_env *env);
int			export(t_cmd *cmd, t_env **env);
int			unset(t_env **env, t_list *args);
int			env(t_cmd *cmd, t_env *envr);
int			exit_cmd(t_cmd *cmd);
int			get_status(int pid, t_env *env);

//cmds utils
t_map		*parse_param(char *param, int *append);

//exec line
int			exec_cmd(t_cmd	*cmd, t_env **env);
int			exec_file(t_cmd *cmd, t_env *env);
int			exec_line(t_tree **line, t_env **env);
int			handel_pipe(t_tree *pipe_tree, t_env **env);
int			redirect(t_tree *tree, t_env **env);

//expanding
char		*ft_expand(char *s, t_env *env);
char		*ft_get_name(void);
t_list		*get_wildcard(void);
t_list		*expand_args(t_list *args, t_env *env, int m);
t_list		*wildcard(t_list *args);

// utils
int			ft_lstlen(t_list *lst);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
int			putstr(char *str);
char		*ft_strdup(char *s1);
char		**ft_split(char *s, char c);
char		*ft_strrchr(char *s, int c);
int			ft_isalnum(int c);
int			putstr(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*get_next_line(int fd);
char		**set_args(char *file, t_list *args);
char		**set_env(t_env *env_list);
char		*locate_cmd(char *cmd, char *path);
void		ft_dup2(int fd1, int fd2);
int			ft_atoi(const char *s);
char		**my_split(char const *s);
void		*ft_memcpy(void *d, const void *s, size_t n);
void		add_cpy(t_list **dest, t_list *src, int type, char *str);
void		ft_putstr_fd(char *s, int fd);
void		expand_redirect(t_cmd *cmd, t_env *env);
int			is_starts(char *str);
char		*ft_get_name2(void);

// export utils
int			print_export(t_map *env);
int			print_export_env(t_env **envr);
void		sort_ex_env(t_map **env);

t_adress	*ft_addrnew(void *addr, int fd);
void		ft_addr_clear(t_adress **head);
void		ft_addr_back(t_adress **head, t_adress *new);
void		*my_malloc(size_t size, int mode);
int			my_open(char *path, int flags, int permissions, int mode);

//lst_utils
t_map		*sort_env(t_map *env);
void		env_free(t_env *env);
int			env_add_back(t_map **env, char *key, char *val);
void		ft_envadd_back(t_map **lst, t_map *new);
int			export_add_back(t_map **env, char *key);
int			is_exist(t_map *env, char *key);
int			list_len(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_dup2(int fd1, int fd2);
t_list		*expand_args(t_list *args, t_env *env, int m);

//errors 
int			file_error(char *file);
int			put_err(char *file, int flag);
int			export_err(char *s);
int			ambiguous_err(char *s);

#endif
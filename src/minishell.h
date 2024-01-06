#ifndef MIMISHELL_H
#define MIMISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
#include <dirent.h>

typedef struct s_map
{
	char			*key;
	char			*val;
	struct s_map	*next;
}	t_map;

typedef struct _s_env
{
	t_map *env;
	t_map *ex_env;
	int		last_exit;
} t_env;

typedef struct s_list
{
	char			*token;
	int				type;
	int				pos; // 1: in quotes, 0: out quotes
	int				expand; // 1: should expand
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
	struct s_adress	*next;
	int index;
}	t_adress;

//////////////////////////////////
# include "parsing/parsing.h"

int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *str1, char *str2, int n);

// cmds
int		echo(t_cmd *cmd, t_env *env);
int		cd(char *path, t_env *env);
char	*get_env(t_env *env, char *key);
int		pwd(t_cmd *cmd, t_env *env);
int		export(t_cmd *cmd, t_env **env);
int 	unset(t_env **env, t_list *args);
int		env(t_cmd *cmd, t_env *envr);

//cmds utils
t_map	*parse_param(char *param, int *append, t_env *env);

//exec line
int		exec_cmd(t_cmd	*cmd, t_env **env);
int		exec_file(t_cmd *cmd, t_env *env);
int		exec_line(t_tree **line, t_env **env);
int		handel_pipe(t_tree *pipe_tree, t_env **env);
int		redirect(t_tree *tree, t_env **env);

//expanding
char	*ft_expand(char *s, t_env *env);
char	*ft_get_name(void);

// utils
char	*ft_strjoin(char *s1,char *s2);
char	*ft_strjoin2(char *s1,char *s2);
size_t	ft_strlen(char *str);
int		putstr(char *str);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
char	*ft_strrchr(char *s, int c);
int		ft_isalnum(int c);
int		putstr(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
void	*my_malloc(size_t size, int mode);
char	**set_args(char *file, t_list *args);
char	**set_env(t_env *env_list);
char	*locate_cmd(char *cmd, char *path);

// export utils
int		print_export(t_map *env, t_map *ex_env);
int		print_export_env(t_env **envr);
void	sort_ex_env(t_map **env);


//tree utils
//void	add_node(t_tree **tree, t_cmd *cmd, int	left);

//lst_utils
t_map	*sort_env(t_map *env);
void	env_free(t_env *env);
int		env_add_back(t_map **env, char *key, char *val);
void	ft_envadd_back(t_map **lst, t_map *new);
int		export_add_back(t_map **env, char *key);
int		is_exist(t_map *env, char *key);
int		list_len (t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_dup2(int fd1, int fd2);

//errors 
int	file_error(char *file);
int	put_err(char *file, int flag);
int	export_err(char *s);

//test utils
//void	(t_tree	*tree); // delete it
void	print_info(t_cmd *cmd); // delete it
void	print_tree(t_tree	*tree, int c); //delete it
void 	print_args(t_list *args); //delete it

// int		ft_strcmp(char *str1, char *str2);
// int		ft_strncmp(char *str1, char *str2, int n);

// cmds
// utils
//int		ft_strlen(char *str);

#endif
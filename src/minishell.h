#ifndef MIMISHELL_H
#define MIMISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct s_map
{
    char            *key;
    char            *val;
    struct s_map    *next;
}    t_map;

typedef struct s_env
{
    t_map *env;
    t_map *ex_env;
}	t_env;


typedef struct s_list
{
	char			*token;
	int				type;
	int				pos; // 1: in quotes, 0: out quotes
	int				expand; // 1: should expand
	int				visited;
	struct s_list	*last;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	int				expand;
	t_list			*args;
	t_list			*redir_in;
	t_list			*redir_out;
	int				flag;
}	t_cmd;

typedef struct s_tree
{
	t_cmd			*cmd;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// int		ft_strcmp(char *str1, char *str2);
// int		ft_strncmp(char *str1, char *str2, int n);

// cmds
int		cd(char *path);
int		ls(t_cmd *cmd);
int		echo(t_cmd *cmd);
int		pwd();
// utils
char	*ft_strjoin(char *s1,char *s2);
//int		ft_strlen(char *str);
int		putstr(char *str);

#endif
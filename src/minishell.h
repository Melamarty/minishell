#ifndef MIMISHELL_H
#define MIMISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct s_env
{
	char	*key;
	char	*val;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**envi;
	t_env			*env;
	int				flag;
}	t_cmd;

typedef struct s_tree
{
	t_cmd			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_list
{
	char			*token;
	int				type;
	struct s_list	*next;
}	t_list;


int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *str1, char *str2, int n);

//mozennou
t_list	*get_tokens(char *expr);
t_list	*ft_lstnew(char *content);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*ft_substr(char const *s, unsigned int start, size_t ln);
size_t	ft_strlen(const char *s);

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
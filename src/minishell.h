#ifndef MIMISHELL_H
#define MIMISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char		**env;
}	t_cmd;

int	ft_strcmp(char *str1, char *str2);
int	ft_strncmp(char *str1, char *str2, int n);
int	cd(char *path);

#endif
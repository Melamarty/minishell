#include "../minishell.h"

int	pwd()
{
	char	path[1024];

	getcwd(path, 1024);
	putstr(path);
	return (1);
}
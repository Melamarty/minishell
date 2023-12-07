#include "../minishell.h"

int	cd(char *path)
{
	if (chdir(path))
		return (1);
	return (0);
}

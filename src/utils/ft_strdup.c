#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*dest;
	size_t	i;

	dest = (char *) my_malloc(ft_strlen(s1) + 1, 0);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
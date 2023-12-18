
#include "parsing.h"

t_map	*ft_envlast(t_map *env)
{
	if (env)
	{
		while (env->next)
		{
			env = env->next;
		}
	}
	return (env);
}

t_map	*ft_envnew(char *key, char *val)
{
	t_map	*res;

	res = (t_map *)malloc(sizeof(t_map));
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->key = key;
	res->val = val;
	return (res);
}

int	ft_envadd_back(t_map **env, t_map *new)
{
	if (!env || !new)
		return (-1);
	if (*env == NULL)
		(*env) = new;
	else
		ft_envlast(*env)->next = new;
	return (0);
}

t_map	*get_env(char **env)
{
	t_map	*res;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	if(!env)
		return (NULL);
	res = NULL;
	while(env[i])
	{
		tmp1 = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		tmp2 = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, ft_strlen(env[i]));
		ft_envadd_back(&res, ft_envnew(tmp1, tmp2));
		i++;
	}
	return (res);
}
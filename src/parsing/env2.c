
#include "parsing.h"

void	swap(t_map *a, t_map *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->val;
	a->key = b->key;
	a->val = b->val;
	b->key = tmp_key;
	b->val = tmp_val;
}

t_map	*sort_env(t_map	*env)
{
	t_map	*p;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		p = env;
		while (p->next)
		{
			if (ft_strncmp(p->key, p->next->key, ft_strlen(p->key) + 1) > 0)
			{
				swap(p, p->next);
				swapped = 1;
			}
			p = p->next;
		}
	}
	return (env);
}


int main(int ac, char **av, char **env)
{
	t_map *tmp;
	t_map *my_env = get_env(env);
	tmp = my_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	printf("\n-----------------------\n\n");
	my_env = sort_env(my_env);
	tmp = my_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:42:47 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/11 13:18:35 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

char	*ft_lstjoin(t_list **tokens)
{
	t_list	*p;
	char	*res;

	p = *tokens;
	res = NULL;
	while (p)
	{
		res = ft_strjoin(res, p->token);
		p = p->next;
	}
	return (res);
}

char	*ft_get_env2(char *s, int len, t_map *env)
{
	if (len == 0)
		return (ft_strdup("$"));
	while (env)
	{
		if (!ft_strncmp(env->key, s, ft_strlen(env->key)))
		{
			if (!ft_isalnum(s[ft_strlen(env->key)]))
				return (ft_strdup(env->val));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

static int	func(char *s, t_list **tokens, t_env *env)
{
	int	i;

	i = 0;
	s++;
	if (!ft_strncmp(s, "?", 1))
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_itoa(env->last_exit), 0));
		return (2);
	}
	if (!ft_strncmp(s, "$", 1))
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(""), 0));
		return (2);
	}
	if (s[i] <= '9' && s[i] >= '0')
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(""), 0));
		return (2);
	}
	while (s[i] && ft_isalnum(s[i]))
		i++;
	ft_lstadd_back(tokens, ft_lstnew(ft_get_env2(s, i, env->env), 0));
	return (i + 1);
}

static int	func5(char *s, t_list **tokens)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(s, 0, i), 0));
	return (i);
}

char	*ft_expand(char *s, t_env *env)
{
	char	*res;
	t_list	*tokens;
	int		i;
	char	*tmp;

	i = 0;
	tokens = NULL;
	res = NULL;
	tmp = s;
	if (!s[0] || !ft_strcmp(s, "$"))
		return (s);
	while (s[i])
	{
		i = 0;
		if (s[i] != '$')
			i = func5(s, &tokens);
		s = s + i;
		i = 0;
		if (s[i] == '$')
			s = s + func(s, &tokens, env);
	}
	res = ft_lstjoin(&tokens);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:40:45 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/09 21:46:47 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

t_map	*get_keyval(char *param, int i)
{
	t_map	*var;

	var = my_malloc(sizeof(t_env), 0);
	var->key = ft_substr(param, 0, i);
	if (!var->key)
		return (NULL);
	var->val = NULL;
	if (param[i + 1])
	{
		if ( param[i] == '+')
			var->val = ft_substr(param, i + 2, ft_strlen(param) - i - 2);
		else
			var->val = ft_substr(param, i + 1, ft_strlen(param) - i - 1);
	}
	else if (param[i] && param[i] == '=')
		var->val = ft_strdup("");
	return (var);
}

void	first_char(char c, int *i)
{
	if (is_valid(c) && (c >= '9' || c <= '0'))
		(*i)++;
}

t_map	*parse_param(char *param, int *append)
{
	int	i;

	i = 0;
	first_char(param[0], &i);
	if (!i)
		return (export_err(param), NULL);
	*append = 0;
	while (param[i] && (param[i] != '='))
	{
		if (param[i] == '+' && param[i + 1] == '=')
		{
			*append = 1;
			break ;
		}
		if (!is_valid(param[i]) || (param[0] >= '0' && param[i] <= '9'))
		{
			export_err(param);
			return (NULL);
		}
		i++;
	}
	return (get_keyval(param, i));
}

t_map	*ft_envnew(char *key, char *val)
{
	t_map	*res;

	res = my_malloc(sizeof(t_map), 0);
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->key = key;
	res->val = val;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:40:45 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/05 12:41:47 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_err(char *s)
{
	write (2, "minishell: export: ", 19);
	while (*s)
	{
		write (2, s, 1);
		s++;
	}
	write (2, ": not a valid identifier\n", 25);
	return (1);
}

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
	if (!var)
		return (NULL);
	var->key = ft_substr(param, 0, i);
	if (!var->key)
		return (NULL);
	var->val = NULL;
	if (param[i + 1])
	{
		if (param[i + 2] && param[i] == '+')
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

t_map	*parse_param(char *param, int *append, t_env *env)
{
	int	i;

	i = 0;
	first_char(param[0], &i);
	if (!i)
		return (print_err(param), NULL);
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
			env->last_exit = 33;
			print_err(param);
			return (NULL);
		}
		i++;
	}
	return (get_keyval(param, i));
}

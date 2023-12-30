/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/30 22:41:39 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var_char2(char *str)
{
	if (str[0] == '?' || str[0] == '!' || str[0] == '*' || str[0] == '@'
		|| ft_isdigit(str[0]))
		return (1);
	return (0);
}

static int	is_var_char(char *str, size_t i)
{
	if (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[0] == '?'
			|| str[0] == '=' || str[0] == ':' || str[0] == '!' || str[0] == '*'
			|| str[0] == '@'))
		return (1);
	return (0);
}

char	*extract_var(char *str, char **ptr)
{
	char		*var;
	size_t		i;

	i = 0;
	var = NULL;
	while (is_var_char(str, i))
	{
		if (is_var_char2(str))
		{
			*ptr = &str[1];
			var = malloc(sizeof(char) * i + 2);
			if (str[0] == '!' || str[0] == '*' || str[0] == '@' || ft_isdigit(str[0]))
				ft_strlcpy(var, str, i + 1);
			else
				ft_strlcpy(var, str, i + 2);
			return (var);
		}
		i++;
	}
	*ptr = &str[i];
	var = malloc(sizeof(char) * i + 1);
	ft_strlcpy(var, str, i + 1);
	return (var);
}

//Searches `envb` for `*str`, return env value,
//or NULL if not found.
char	*get_env_value(t_env *envb, char **str)
{
	size_t	str_len;

	str_len = ft_strlen(*str);
	while (envb)
	{
		if (!ft_strncmp(envb->var_str, *str, str_len)
			&& envb->var_str[str_len] == '=')
		{
			free (*str);
			*str = ft_strdup(&envb->var_str[str_len + 1]);
			if (!(*str))
				return (NULL);
			return (*str);
		}
		else
		{
			envb = envb->next;
		}
	}
	free (*str);
	*str = NULL;
	return (*str);
}

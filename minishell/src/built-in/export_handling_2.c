/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handling_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:35:32 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/31 12:07:27 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//return the env_node matching the str or NULL if no match
t_env	*get_env_node(t_env *lst, char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	while (lst)
	{
		if (!ft_strncmp(lst->var_str, str, str_len))
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

static char	**allocate_and_copy(char *str)
{
	char	**ret_tab;

	ret_tab = malloc(sizeof(char *) * 2);
	if (!ret_tab)
		return (NULL);
	ret_tab[0] = ft_strdup(str);
	if (!ret_tab[0])
	{
		free(ret_tab);
		return (NULL);
	}
	ret_tab[1] = NULL;
	return (ret_tab);
}

static char	**split_and_manage(char *var, char *equal, char *plus)
{
	char	**ret_tab;

	if (plus && *(plus + 1) == '=')
	{
		ret_tab = ft_split(var, '+');
		free(ret_tab[1]);
		ret_tab[1] = ft_strdup(equal + 1);
		if (!ret_tab[1])
		{
			free(ret_tab);
			return (NULL);
		}
	}
	else if (equal && !plus)
		ret_tab = ft_split(var, '=');
	return (ret_tab);
}

char	**ft_split_value(char *var)
{
	char	*equal;
	char	*plus;
	char	**ret_tab;

	equal = ft_strchr(var, '=');
	if (!equal)
		return (allocate_and_copy(var));
	plus = ft_strchr(var, '+');
	ret_tab = split_and_manage(var, equal, plus);
	return (ret_tab);
}

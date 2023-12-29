/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handling_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:35:32 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/29 15:12:27 by esilbor          ###   ########.fr       */
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
		if (!ft_strncmp(lst->var_str, str, ft_strlen(str))
			&& lst->var_str[str_len] == '=')
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

// split the input line for export according to '=' or "+="
char	**ft_split_value(char *var)
{
	char	*equal;
	char	*plus;
	char	**ret_tab;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		ret_tab = malloc(sizeof(char *) * 2);
		if (!ret_tab)
			return (NULL);
		ret_tab[0] = ft_strdup(var);
		if (!ret_tab[0])
		{
			free(ret_tab);
			return (NULL);
		}
		ret_tab[1] = NULL;
		return (ret_tab);
	}
	plus = ft_strchr(var, '+');
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
	if (equal && !plus)
		ret_tab = ft_split(var, '=');
	return (ret_tab);
}

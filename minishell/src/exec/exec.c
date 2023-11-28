/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/25 00:04:44 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_set	*init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb)
{
	t_env	*p;
	char	*path;

	p = get_env_node(envb, "PATH");
	if (!p || !p->var_str)
		return (NULL);
	path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
	if (!path)
		return (NULL);
	*set = malloc(sizeof(t_set));
	if (!(*set))
		return (free (path), NULL);
	ft_memset(*set, 0, sizeof(t_set));
	(*set)->cmd_nb = ft_tab_len((char **)cmd_struct_tab);
	(*set)->paths = ft_split(path, ':');
	free (path);
	(*set)->envb = envb;
	(*set)->cmd_set = cmd_struct_tab;
	ft_print_tab((void **)(*set)->paths, "envb");
	ft_print_struct_tab((*set)->cmd_set);
	return (*set);
}

char	**env_to_tab(t_env *lst)
{
	int		i;
	int		len;
	char	**tab;

	i = 0;
	len = ft_lstsize((t_list *)lst);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = NULL;
	while (lst)
	{
		tab[i] = ft_strdup(lst->var_str);
		if (!tab[i])
			return (ft_free_tab((void **)tab), NULL);
		lst = lst->next;
		i ++;
	}
	return (tab);
}

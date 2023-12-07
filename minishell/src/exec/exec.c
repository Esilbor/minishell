/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 07:31:25 by esilbor          ###   ########.fr       */
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
	if (cmd_struct_tab && cmd_struct_tab[0])
		(*set)->cmd_nb = ft_tab_len((char **)cmd_struct_tab);
	else
		(*set)->cmd_nb = 0;
	(*set)->paths = ft_split(path, ':');
	free (path);
	(*set)->env_lst = envb;
	(*set)->envp = env_to_tab(envb);
	(*set)->cmd_set = cmd_struct_tab;
	(*set)->pid = NULL;
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

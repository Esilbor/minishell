/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/11 16:28:07 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	**assign_paths(t_set **set, t_env *envb)
// {
// 	char	*path;
// 	t_env	*p;

// 	p = get_env_node(envb, "PATH");
// 	if (!p || !p->var_str)
// 		return (NULL);
// 	path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
// 	if (!path)
// 		return (NULL);
// 	(*set)->paths = ft_split(path, ':');// a proteger
// 	if (!(*set)->paths)
// 		return (NULL);
// 	free (path);
// 	return ((*set)->paths);
// }

// t_set	*init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb)
// {
// 	*set = malloc(sizeof(t_set));
// 	if (!(*set))
// 		return (/* free (path),  */NULL);
// 	ft_memset(*set, 0, sizeof(t_set));
// 	if (cmd_struct_tab && cmd_struct_tab[0])
// 		(*set)->cmd_nb = ft_tab_len((char **)cmd_struct_tab);
// 	else
// 		(*set)->cmd_nb = 0;

// 	(*set)->env_lst = envb;
// 	assign_paths(set, envb);
// 	(*set)->envp = env_to_tab(envb);
// 	(*set)->cmd_set = cmd_struct_tab;
// 	(*set)->pid = NULL;
// 	return (*set);
// }

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
	(*set)->paths = ft_split(path, ':');// a proteger
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/22 12:59:52 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*to place in the exec section: */
// t_set	*set;
//
// set = NULL;
// init_set(&set, cmd_struct_tab, envb);


// to put in .h
// typedef struct t_set
// {
// 	char			**paths;
// 	int				cmd_nb;
// 	struct s_env	*envb; // would give access to envb if needed
// 	struct s_cmd	**cmd_set; // would give access to cmd_struct_tab if needed
// }	t_set;

t_set   *init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb)
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
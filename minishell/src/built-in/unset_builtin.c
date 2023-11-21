/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:15:18 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/21 14:23:19 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Unset prend en compte le contenu de $?
// unset He$?llo == unset He0llo || unset He1llo

void	ft_remove_env_node(t_env **head, char *varp)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	if (tmp != NULL && ft_strncmp(tmp->var_str, varp, ft_strlen(varp)) == 0)
	{
		*head = tmp->next;
		free(tmp->var_str);
		free(tmp);
		return ;
	}
	while (tmp != NULL && ft_strncmp(tmp->var_str, varp, ft_strlen(varp)) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp->var_str);
	free(tmp);
}

int	do_unset(char **cmd_tab, t_env **env)
{
	int	cmd_nb;
	int	i;
	int	ret;

	cmd_nb = ft_tab_len(cmd_tab);
	i = 0;
	ret = 0;
	while (++i < cmd_nb)
	{
		if (cmd_is_valid(cmd_tab, i, &ret))
			ft_remove_env_node(env, cmd_tab[i]);
	}
	return (update_ret(env, ret));
}

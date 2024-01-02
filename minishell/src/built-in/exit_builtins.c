/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/02 22:21:02 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	do_exit(char **cmd_tab, t_env **env)
void	do_exit(t_set *set, int index)
{
	if (ft_tab_len(set->cmd_set[index]->cmd) == 1)
	{
		candy_crush(set);
		exit(g_exit_val);
	}
	if (!exit_parser(set->cmd_set[index]->cmd)
		&& ft_tab_len(set->cmd_set[index]->cmd) > 1
		&& set->cmd_set[index]->cmd[1])
	{
		if (ft_atol(set->cmd_set[index]->cmd[1]) > 255)
		{
			g_exit_val = ft_atol(set->cmd_set[index]->cmd[1]) % 256;
		}
		else
		{
			g_exit_val = ft_atol(set->cmd_set[index]->cmd[1]);
		}
		candy_crush(set);
		exit(g_exit_val);
	}
}

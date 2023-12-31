/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 19:50:25 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	do_exit(char **cmd_tab, t_env **env)
void	do_exit(t_set *set, int index)
{
	int	exit_ret;

	exit_ret = 0;
	if (ft_tab_len(set->cmd_set[index]->cmd) == 1)
	{
		candy_crush(set);
		exit (exit_ret);
	}
	if (!exit_parser(set->cmd_set[index]->cmd)
		&& ft_tab_len(set->cmd_set[index]->cmd) > 1
		&& set->cmd_set[index]->cmd[1])
	{
		if (ft_atol(set->cmd_set[index]->cmd[1]) > 255)
			exit_ret = ft_atol(set->cmd_set[index]->cmd[1]) % 256;
		else
			exit_ret = ft_atol(set->cmd_set[index]->cmd[1]);
		candy_crush(set);
		exit(exit_ret);
	}
}

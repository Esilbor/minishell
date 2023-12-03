/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/03 16:14:30 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_msg(int msg)


int	do_exit(char **cmd_tab, t_env **envb)
{
	if (ft_tab_len(cmd_tab) > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		// flush_shell
		exit(1);
	}
}
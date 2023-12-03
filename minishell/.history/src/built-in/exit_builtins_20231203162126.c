/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/03 16:21:26 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_msg(char *arg, int msg)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd(": exit:", 2);
	ft_putstr_fd(, 2);
}

int	do_exit(char **cmd_tab, t_env **envb)
{
	(void) envb;
	if (ft_tab_len(cmd_tab) > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		// candy_crush
		exit(1);
	}
	return (0);
}
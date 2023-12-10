/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:03:51 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/10 12:52:11 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



// void	ft_close_and_free(t_set *set)
// {
// 	if (set->pipe)
// 	{
// 		// ft_close_pipes(set); //????
// 		free(set->pipe[0]);
// 		free(set->pipe[1]);
// 		free(set->pipe);
// 	}
// 	candy_crush(set);
// }

// void	ft_quit_shell(t_set *set, t_env *envb, t_cmd **cmd_struct_tab)
// {
// 	rl_clear_history();
// 	// ft_printf("exit\n"RESET);
// 	ft_free_env_lst(envb);
// 	free_cmd_struct_tab(cmd_struct_tab);
// 	free(set);
// }

// void	free_shell(t_set *set, char *input, t_cmd **cmd_struct_tab)
// {
// 	// ft_free_tab((void **)set->paths); //segf
// 	// ft_free_tab((void **)set->envp);
// 	free(set);
// 	free_cmd_struct_tab(cmd_struct_tab);
// 	free(input);
// }


//close pipes, pid_tab + candy-crush + exit
// void	close_crush_exit(char *msg, t_set *set, int do_exit, int exit_ret)
// {
// 	if (msg)
// 		ft_putstr_fd(msg, 2);
// 	ft_close_pipes(set);
// 	ft_free_tab((void **)set->pid);
// 	candy_crush(set);
// 	if (do_exit)
// 		exit(exit_ret);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/04 17:23:58 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipe_set(t_set *set)
{
	set->pipe = malloc(sizeof(int *) * 2);
	if (!set->pipe)
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe set", 2));
	set->pipe[0] = malloc(sizeof (int) * 2);
	if (!set->pipe[0])
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe[0]", 2));
	set->pipe[1] = malloc(sizeof (int) * 2);
	if (!set->pipe[1])
	{
		free (set->pipe[0]);
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe[1]", 2));
	}
	set->pipe[0][0] = 0;
	set->pipe[0][1] = 0;
	set->pipe[1][0] = 0;
	set->pipe[1][1] = 0;
}

void	init_pid_tab(t_set *set)
{
	int	i;

	i = -1;
	set->pid = malloc(sizeof (pid_t) * set->cmd_nb);
	if (!set->pid)
		return (ft_putstr_fd("could not malloc pid_tab", 2));
	while (++i < set->cmd_nb)
		set->pid[i] = 0;
}



void ft_execve(t_set *set, int index)
{
	int i;
	char *cmd_path;

	i = 0;
	// if (!set->paths)
	// {
	// 	// erre split

	// }
	if (set->paths && (!ft_strchr(set->cmd_set[index]->cmd[0], '/')))
	{
		cmd_path = set_path_cmd(set, set->cmd_set[index]->cmd[0]);
		if (!cmd_path)
		{
			// free , close ... exit
			ft_close_and_free(set);
			exit(127); // a verifier avec update_ret
		}
		execve(cmd_path, set->cmd_set, set->envp);
	}
	else
	{
		if (access(set->cmd_set[index]->cmd[0], X_OK | F_OK) == 0)
		{
			ft_close_and_free(set);
			exit(127); // a verifier avec update_ret
		}
		exeve(set->cmd_set[index]->cmd[0], set->cmd_set, set->envp);
	}
	ft_close_and_free(set);
	exit(update_ret(set->env_lst, 126)); // a verifier
}

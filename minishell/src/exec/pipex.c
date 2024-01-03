/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:47 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/03 16:07:35 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve(t_set *set, int index)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (set->paths && (!ft_strchr(set->cmd_set[index]->cmd[0], '/')))
	{
		cmd_path = set_path_cmd(set, set->cmd_set[index]->cmd[0]);
		if (!cmd_path)
			exit_err(set, 127);
		execve(cmd_path, set->cmd_set[index]->cmd, set->envp);
	}
	else
	{
		if (access(set->cmd_set[index]->cmd[0], X_OK | F_OK) == 0)
			execve(set->cmd_set[index]->cmd[0], set->cmd_set[index]->cmd,
				set->envp);
		print_cmd_not_found(set->cmd_set[index]->cmd[0]);
		exit_err(set, 127);
	}
	free(cmd_path);
	exit_err(set, 126);
}

pid_t	ft_fork(t_set *set, int index)
{
	pid_t	pid;

	if (index < set->cmd_nb)
		if (pipe(set->pipe[index % 2]) == -1)
			ft_error(ERR_PIPE, set);
	pid = fork();
	if (pid == -1)
		ft_error(ERR_FORK, set);
	if (pid == 0)
	{
		ft_dup2(set, index);
		if (set->cmd_set[index]->cmd[0]
			&& is_builtin(set->cmd_set[index]->cmd) == 1)
			do_builtins(set, index);
		else if (set->cmd_set[index]->cmd[0])
		{
			signals_simple();
			ft_close_pipes(set);
			ft_execve(set, index);
		}
		exit_err(set, g_exit_val);
	}
	if (index)
		close_pipe(set, index);
	return (pid);
}

// Waits for child processes to finish.
void	ft_wait(t_set *set)
{
	int	status;
	int	lastpid;

	while (set->cmd_nb > 0)
	{
		lastpid = wait(&status);
		if (set->pid == lastpid)
		{
			if (WIFEXITED(status))
				update_ret(&set->env_lst, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				update_ret(&set->env_lst, 128 + WTERMSIG(status));
		}
		set->cmd_nb--;
	}
	ft_handle_signals();
}

bool	is_single_builtin(t_set *set, int index)
{
	if (is_builtin(set->cmd_set[index]->cmd) && set->cmd_nb == 1)
	{
		if (!set->cmd_set[index]->input && !set->cmd_set[index]->output)
			return (true);
	}
	return (false);
}

void	ft_pipex(t_set *set)
{
	int		i;
	pid_t	last_pid;

	i = 0;
	if (set->cmd_set[i]->cmd[0] && is_single_builtin(set, i))
	{
		do_builtins(set, i);
	}
	else
	{
		while (i < set->cmd_nb)
		{
			ign_sigint();
			last_pid = ft_fork(set, i);
			set->pid = last_pid;
			i++;
		}
		ft_wait(set);
		close_pipe(set, i);
	}
}

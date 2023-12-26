/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/26 16:48:21 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void ft_execve(t_set *set, int index)
{
	char *cmd_path;
	
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
			execve(set->cmd_set[index]->cmd[0], set->cmd_set[index]->cmd, set->envp);
		print_cmd_not_found(set->cmd_set[index]->cmd[0]);
		exit_err(set, 127);
	}
	exit_err(set, 126);
}

pid_t	ft_fork(t_set *set, int index)
{
	pid_t	pid;

	if (index < set->cmd_nb)
		if (pipe(set->pipe[index % 2]) == -1)
			ft_error(ERR_PIPE, set);
	ign_sigint(); // ignore sigquit (ctrl-\) + sigint (ctrl-c)	
	pid = fork();
	if (pid == -1)
		ft_error(ERR_FORK, set);
	if (pid == 0)
	{
		ft_dup2(set, index);
		if (set->cmd_set[index]->cmd[0] && is_builtin(set->cmd_set[index]->cmd) == 1)
			do_builtins(set, index); 
		else if (set->cmd_set[index]->cmd[0])
		{
			signals_simple(); // fonction par defaut
			ft_close_pipes(set);	
			ft_execve(set, index);
		}
		exit_err(set, 1);
	}
	if (index)
		close_pipe(set, index);
	return (pid);
}

// Waits for child processes to finish.
void	ft_wait(t_set *set)
{
	int status;
	int lastpid;

	while (set->cmd_nb > 0)
	{
		lastpid = wait(&status);
		//if (set->pid[set->cmd_nb - 1] == lastpid)
		if (set->pid == lastpid)
		{
			if (WIFEXITED(status))
				update_ret(&set->env_lst, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				update_ret(&set->env_lst, 128 + WTERMSIG(status));
		}
		set->cmd_nb--;		
	}
	ft_handle_signals(); // ignor sigquit (ctrl-\)
	
}

// Macro: int WIFEXITED (int status) --> when the child erminated with ------------> exit 
// Macro: int WIFSIGNALED (int status) --> if the child process terminated because it received a signal that was not handled.
// Macro: int WTERMSIG (int status) ---> it  returns the signal number of the signal that terminated the child process
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
	int	i;
	pid_t last_pid;

	i = 0;
	if (set->cmd_set[i]->cmd[0] && is_single_builtin(set, i))
	{
		do_builtins(set, i);
	}
	else
	{
		while (i  < set->cmd_nb)
		{
			last_pid = ft_fork(set, i);
			//set->pid[i] = last_pid;
			set->pid = last_pid;
			i++;
		}
		ft_wait(set);
		close_pipe(set, i);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/15 10:43:54 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// closes pipe file descriptors if exist
void	ft_close_pipes(t_set *set)
{
	if (set->pipe[0][0])
		close(set->pipe[0][0]);
	if (set->pipe[0][1])
		close(set->pipe[0][1]);
	if (set->pipe[1][0])
		close(set->pipe[1][0]);
	if (set->pipe[1][1])
		close(set->pipe[1][1]);
}

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

void	exit_err(t_set *set, int err_nb)
{
	ft_close_pipes(set);
	free_redirections(set->cmd_set);
	free_after_builtin(set);
	exit(err_nb); // a verifier avec update_ret
}

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

void	close_pipe(t_set *set, int index)
{
	close(set->pipe[(index + 1) % 2][0]);
	close(set->pipe[(index + 1) % 2][1]);
}

void	free_after_builtin(t_set *set)
{
	ft_free_env_lst(set->env_lst);
	free(set->pipe[0]);
	free(set->pipe[1]);
	free(set->pipe);
	ft_free_tab((void **)set->paths);
	ft_free_tab((void **)set->envp);
	free_cmds((t_cmd **)set->cmd_set);
	free(set->pid);
	free (set);
}

pid_t	ft_fork(t_set *set, int index)
{
	pid_t	pid;

	if (index < set->cmd_nb)
	{
		if (pipe(set->pipe[index % 2]) == -1)
			return (printf("ERR_PIPE\n"));//free close ...
	}
	ign_sigint(); // ignore sigquit (ctrl-\) + sigint (ctrl-c)
	pid = fork();
	if (pid == -1)
		return (printf("ERR_PID\n"));//free close ...
	if (pid == 0)
	{
		ft_dup2(set, index);
		if (set->cmd_set[index]->cmd[0] && is_builtin(set->cmd_set[index]->cmd)== 1)
		{
			do_builtins(set, index); // je ne me souviens plus pourquoi jai rajoute ca
			// exit_err(set, 0);
			// ft_close_pipes(set);
			// free_redirections(set->cmd_set);
			// free_after_builtin(set);

			// free_redirections((t_cmd **)set->cmd_set);
			// free_after_builtin(set);
			// exit(0); // recuperer et exit$?
		}
		if (set->cmd_set[index]->cmd[0])
		{
			signals_simple(); // fonction par defaut
			ft_execve(set, index);
			// free_after_builtin(set);
		}
		else
		{
			free_redirections((t_cmd **)set->cmd_set);
			free_after_builtin(set);
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

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			update_ret(&set->env_lst, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			update_ret(&set->env_lst, 128 + WTERMSIG(status));			
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
		do_builtins(set, i);
	else
	{
		while (i < set->cmd_nb)
		{
			last_pid = ft_fork(set, i);
			set->pid[i] = last_pid;
			i++;
		}
		ft_wait(set);
	}
}

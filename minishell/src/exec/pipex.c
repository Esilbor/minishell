/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:58:25 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/02 21:11:35 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe

void ft_dup2(t_data *data, int index)
{
   int	fd_stdin;
	int	fd_stdout;

	fd_stdin = ft_stdin(data, index);
	fd_stdout = ft_stdout(data, index);
    if (fd_stdin != 0)
		close(fd_stdin);
	if (fd_stdout != 1)
		close(fd_stdout);
    // if (index == 0)
    // gerer stdin et stdout 
	// 	ft_dup2_first(data, index, fd_stdin, fd_stdout);
	// else
    // 
	// 	ft_dup2_n(data, index, fd_stdin, fd_stdout);
    
}

int	ft_stdin(t_data *data, int index)
{
     int	fd_stdin = 0;
	
    // si on a une redirction : 
    if (data->lst_cmd[index]->input_redir)
    {
        fd_stdin = open(*data->lst_cmd[index]->input_redir, O_RDONLY);
        if (fd_stdin < 0)
			printf("Error : File descriptor stdin\n");
        
    }
    else  if (data->lst_cmd[index]->eof)
    {
        fd_stdin = open(data->lst_cmd[index]->heredoc_path, O_RDONLY);
        if (fd_stdin < 0)
			printf("Error : File descriptor stdin\n");
        
    }  
    return (fd_stdin);
    
}

int	ft_stdout(t_data *data, int index)
{
    int	fd_stdout = 1;
     if (data->lst_cmd[index]->input_redir)
    {
        if (data->lst_cmd[index]->append == 1)
        {
            fd_stdout = open(*data->lst_cmd[index]->input_redir,
					O_RDWR | O_APPEND | O_CREAT, 0644);
            if (fd_stdout < 0)
			    printf("Error : File descriptor stdin\n");
        }
        else
        {
			fd_stdout = open(*data->lst_cmd[index]->input_redir,
					O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd_stdout < 0)
				printf("File descriptor error, stdout\n");
		}  
        
    }
     return (fd_stdout);
}


int	ft_fork(t_data *data, int index)
{
	pid_t	child_pid;

	child_pid = fork();
    pid_alloc(data);
	if (child_pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (child_pid == 0)
	{
		ft_dup2(data, index); // (old, new)
		//close(fd[?]);
		if (is_builtin(&data->lst_cmd[index]->cmd[0]) == 1)
		{
			do_builtins(&data->lst_cmd[index]->cmd[0], &data->lst_env);
		}
		if (&data->lst_cmd[index]->cmd[0])
			ft_exec_cmd(data, index);
		exit(1);
	}
	// else waitpid parent???
	// if (index)
	// {
	//     close(data->pipes[(index + 1) % 2][0]);
	//     close(data->pipes[(index + 1) % 2][1]);
	// }
	return (child_pid);
}

int	**pipes_alloc(t_data *data)
{
	int	index;
    int i;
	
	index = 0;
	data->pipes = (int **)malloc(sizeof(int *) * 2);
	if (!data->pipes)
		return (printf("ERR_MAL"), NULL);
	
    i = 0;
    while (index < 2)
    {
        data->pipes[index] = malloc(sizeof(int) * 2);
        if (!data->pid[index])
		    return (printf("ERR_MAL"), NULL);
        while (i < 2)
        {
             data->pipes[index][i] = 0;
             i++;
        }
		index++;
    }
	return (data->pipes);
}

int	pid_alloc(t_data *data)
{
    int	count;
    int	index;

    index = 0;
    count = data->cmds_nb;
	data->pid = malloc(sizeof(int) * (count + 1)); // pid_t
	if (!data->pid)
		return (printf("ERR_MALOC"), 0);
    while (index < count)
	{
		data->pid[index] = 0;
        index++;
    }
    data->pid[index] = 0;
		//pipe(&data->pid[index]);
	return (*data->pid);
}
    


void	init_fd(int **fd, t_cmd *cmd, int index)
{
	if (index == 0 && cmd)
	{
		if (cmd->fd_out == 1)
			cmd->fd_out = fd[index][1];
	}
	else if (index != 0 && cmd)
	{
		if (cmd->fd_in == 0)
			cmd->fd_in = fd[index - 1][0];
		if (cmd->fd_out == 1)
			cmd->fd_out = fd[index][1];
	}
	else if (index != 0 && !cmd)
		if (cmd->fd_in == 0)
			cmd->fd_in = fd[index - 1][0];
}

int	**init_pipes(t_data *data)
{
	int		i;
	int		cpt;
	int		**fd;
	t_cmd	**cmd;

	i = 0;
	cmd = data->lst_cmd;
	cpt = data->cmds_nb;
    fd = pipes_alloc(data);
	if (!fd)
		exit(1);
	while (cmd[i])
	{
		init_fd(fd, *cmd, i);
		i++;
		cpt++;
	}
	return (fd);
=======
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/07 08:24:31 by esilbor          ###   ########.fr       */
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
	// int i;
	char *cmd_path;

	// i = 0;
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
			ft_close_pipes(set);
			exit(127); // a verifier avec update_ret
		}
		execve(cmd_path, set->cmd_set[index]->cmd, set->envp); //mod
	}
	else
	{
		if (access(set->cmd_set[index]->cmd[0], X_OK | F_OK) == 0)
		{
			execve(set->cmd_set[index]->cmd[0], set->cmd_set[index]->cmd, set->envp);
		}
		ft_close_pipes(set);
		exit(127); // a verifier avec update_ret
	}
	ft_close_pipes(set);
	exit(update_ret(&set->env_lst, 126)); // a verifier
}


void	close_pipe(t_set *set, int index)
{
	close(set->pipe[(index + 1) % 2][0]);
	close(set->pipe[(index + 1) % 2][1]);
}



pid_t	ft_fork(t_set *set, int index)
{
	pid_t	pid;

	if (index < set->cmd_nb)
	{
		if (pipe(set->pipe[index % 2]) == -1)
			return (printf("ERR_PIPE\n"));//free close ...
	}
	pid = fork();
	if (pid == -1)
		return (printf("ERR_PID\n"));//free close ...
	if (pid == 0)
	{
		ft_dup2(set, index);
		if (is_builtin(set->cmd_set[index]->cmd)== 1)
		{
			do_builtins(set, index);
			// free env_lst , pid_tab, pipes, cmd_struct_tab, paths, envp
			// close_crush_exit(NULL, set, 1, 0);
			exit(0);
		}
		if (set->cmd_set[index]->cmd[0])
		{
			ft_execve(set, index);
		}

		// close_crush_exit(NULL, set, 1, 1);
		exit(1); // if execve fails
	}
	if (index)
		close_pipe(set, index);
	return (pid);
}

// Waits for child processes to finish.
void	ft_waitpid(t_set *set)
{
	int	i;
	// int status;
	// int	save_status;
	// save_status = 0;
	i = 0;
	while (i < set->cmd_nb && set->pid[i])
	{
		waitpid(set->pid[i], NULL/* , &status */, 0);
		i++;
	}
	// save_status = status;
	// if (WIFSIGNALED(save_status))
	// 	status = 128 + WTERMSIG(save_status);
	// else if (WIFEXITED(save_status))
	// 	status = WEXITSTATUS(save_status);
	// else
	// 	status = save_status;
	// g_last_status = status;
}

void	ft_pipex(t_set *set)
{
	int	i;
	pid_t last_pid;

	i = 0;
	while (i < set->cmd_nb)
	{
		last_pid = ft_fork(set, i);
		set->pid[i] = last_pid;
		i++;
	}
	ft_waitpid(set);
	// close_crush_exit(NULL, set, 0, 0);
	// exit(0);
>>>>>>> main
}

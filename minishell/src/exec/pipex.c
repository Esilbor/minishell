/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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
}

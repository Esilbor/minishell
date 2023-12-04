/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:28:56 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/04 19:28:29 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



int  open_input(t_set *set, int index)
{
	int fd_stdin;
	int i;

	i = 0;
	fd_stdin = 0;
	while (set->cmd_set[index]->input_redir[i])
	{
		if (fd_stdin)
			close(fd_stdin);
		fd_stdin = open (set->cmd_set[index]->input_redir[i], O_RDONLY);
		if (fd_stdin < 0)
		{
			printf("ERR_FD\n");
			// close pipes ...
			exit(1);
		}
		i++;
	}
	return (fd_stdin);
}

int	ft_open_stdin(t_set *set, int index)
{
	int	fd_stdin;
	int i;

	fd_stdin = 0;
	i = 0;
	if (set->cmd_set[index]->input_redir[0]) // redirections
		fd_stdin = open_input(set, index);
	// eof

	return (fd_stdin);

}


int	ft_open_stdout(t_set *set, int index)
{
	int	fd_stdout;

	fd_stdout = 1;
	if (set->cmd_set[index]->output)
	{
		while (set->cmd_set[index]->output)
		{
			if(set->cmd_set[index]->output->type == APPEND)
			{
				fd_stdout = open(set->cmd_set[index]->output,
					O_RDWR | O_APPEND | O_CREAT, 0644);
			}
			else
			{
				fd_stdout = open(set->cmd_set[index]->output,
						O_RDWR | O_TRUNC | O_CREAT, 0644);
			}
			if (fd_stdout < 0)
			{
				printf("ERR_FD\n");
				// close pipes ...
				exit(1);
			}
			set->cmd_set[index]->output = set->cmd_set[index]->output->next;
		}
	}
	return (fd_stdout);

}



void ft_dup2(t_set *set, int index)
{
	int	fd_stdin;
	int	fd_stdout;

	fd_stdin = ft_open_stdin(set, index);
	fd_stdout = ft_open_stdout(set, index);



	// if (fd_stdin != 0)
	// 	close(fd_stdin);
	// if (fd_stdout != 1)
	// 	close(fd_stdout);



}

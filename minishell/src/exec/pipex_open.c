/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:28:56 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/02 18:53:43 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_open_stdin(t_set *set, int index)
{
	int	fd_stdin;

	fd_stdin = 0;
	if (set->cmd_set[index]->input)
		fd_stdin = open(set->cmd_set[index]->input->word, O_RDONLY);
	return (fd_stdin);
}

int	ft_open_stdout(t_set *set, int index)
{
	int		fd_stdout;
	t_lexer	*lex;

	fd_stdout = 1;
	if (set->cmd_set[index]->output)
	{
		lex = set->cmd_set[index]->output;
		if (lex->type == APPEND)
			fd_stdout = open(lex->word, O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			fd_stdout = open(lex->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd_stdout < 0)
			ft_putstr_fd("ERR_FD\n", 2);
	}
	return (fd_stdout);
}

void	ft_dup2_first(t_set *set, int index, int fd_stdin, int fd_stdout)
{
	if (fd_stdin && dup2(fd_stdin, 0) == -1)
			exit_err(set, 1);
	if (fd_stdout != 1 && dup2(fd_stdout, 1) == -1)
			exit_err(set, 1);
	if (set->cmd_nb > 1 && fd_stdout == 1)
	{
		if (dup2(set->pipe[index][1], 1) == -1 || close(set->pipe[index][0]) == -1)
		{
			exit_err(set, 1);
		}
	}
}

void	ft_dup2_multpl(t_set *set, int index, int fd_stdin, int fd_stdout)
{
	if (fd_stdin)
	{
		if (dup2(fd_stdin, 0) == -1)
			exit_err(set, 1);
	}
	else
	{
		if (dup2(set->pipe[(index + 1) % 2][0], 0) == -1)
			exit_err(set, 1);
	}
	if ((index + 1) == set->cmd_nb)
	{
		if (dup2(fd_stdout, 1) == -1)
			exit_err(set, 1);
	}
	else
	{
		if (fd_stdout != 1 && dup2(fd_stdout, 1) == -1)
			exit_err(set, 1);
		else if (dup2(set->pipe[index % 2][1], 1) == -1)
			exit_err(set, 1);
	}
}

void ft_dup2(t_set *set, int index)
{
	int	fd_stdin;
	int	fd_stdout;

	fd_stdin = ft_open_stdin(set, index);
	fd_stdout = ft_open_stdout(set, index);

	if (index == 0)
		ft_dup2_first(set, index, fd_stdin, fd_stdout);
	else
		ft_dup2_multpl(set, index, fd_stdin, fd_stdout);
	if (index)
	{
		close_pipe(set, 0);
		close_pipe(set, 1);
	}
	if (fd_stdin != 0)
		close(fd_stdin);
	if (fd_stdout != 1)
		close(fd_stdout);
	
}

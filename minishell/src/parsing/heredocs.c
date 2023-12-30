/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 18:05:27 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_heredoc(t_env *env, t_lexer *lex, char *limiter)
{
	int		fd;

	fd = open(lex->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("could not open heredoc\n", 2);
		exit (1);
	}
	fill_heredoc(env, fd, limiter);
	close(fd);
}

int	init_heredocs(t_env *env, t_cmd **cmd_tab)
{
	int		i;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
			if (modify_limiter_nodes(env, cmd_tab[i]->input, i) < 0)
				return (-1);
		i++;
	}
	return (0);
}

// Helper function to read and write heredoc lines
static void	read_and_write_heredoc(int fd, char *limiter, t_env *env)
{
	char	*buf;
	size_t	eof_len;

	eof_len = ft_strlen(limiter);
	while (1)
	{
		buf = readline("heredoc> ");
		update_ret(&env, g_exit_val);
		if (!buf || (buf[0] && eof_len == ft_strlen(buf)
				&& !ft_strncmp(limiter, buf, eof_len)))
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		write(fd, "\n", 1);
		free(buf);
	}
}

void	fill_heredoc(t_env *env, int fd, char *limiter)
{
	int	dup_stdin;

	dup_stdin = dup(STDIN_FILENO);
	update_ret(&env, 0);
	signal_heredoc();
	read_and_write_heredoc(fd, limiter, env);
	g_exit_val = 0;
	dup2(dup_stdin, STDIN_FILENO);
	ft_handle_signals();
	close(dup_stdin);
}

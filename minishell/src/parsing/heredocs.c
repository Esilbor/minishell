/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/04 05:47:18 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_heredoc(char	*buf, t_env *env, int fd, char *limiter)
{
	int		dup_stdin;

	dup_stdin = dup(STDIN_FILENO);
	update_ret(&env, 0);
	signal_heredoc();
	while (1)
	{
		buf = readline("heredoc> ");
		update_ret(&env, g_exit_val);
		if (!buf)
		{
			ft_printf("\n");
			break ;
		}
		if (buf[0] && (ft_strlen(limiter) == ft_strlen(buf))
			&& !ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(buf, fd);
		write(fd, "\n", 1);
		free(buf);
	}
	dup2(dup_stdin, STDIN_FILENO);
	closes_heredoc(fd, dup_stdin);
	ft_handle_signals();
}

void	create_heredoc(t_env *env, t_lexer *lex, char *limiter)
{
	int		fd;
	char	*buf;

	buf = NULL;
	fd = open(lex->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("could not open heredoc\n", 2);
		exit(1);
	}
	fill_heredoc(buf, env, fd, limiter);
	close(fd);
}

//void	init_heredocs(t_env *env, t_cmd **cmd_tab)
int	init_heredocs(t_env *env, t_cmd **cmd_tab)
{
	int	i;

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

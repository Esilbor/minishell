/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/10 16:26:32 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exit(int fd, int dup_stdin)
{
	printf("exit fill_heredoc\n");
	close(dup_stdin);
	close(fd);
	return (1);
}

//void	fill_heredoc(char	*buf, t_env *env, int fd, char *limiter)
int	fill_heredoc(char	*buf, t_env *env, int fd, char *limiter)
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
	if (dup2(dup_stdin, STDIN_FILENO) == -1)
		return (free(limiter), ft_exit(fd, dup_stdin));
	closes_heredoc(fd, dup_stdin);
	return (0);
}

//void	create_heredoc(t_env *env, t_lexer *lex, char *limiter)
int	create_heredoc(t_env *env, t_lexer *lex, char *limiter)
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
	if (fill_heredoc(buf, env, fd, limiter) == 1)
	{
		close(fd);
		return (-1);
	}
	ft_handle_signals();
	return (0);
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

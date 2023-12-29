/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/29 22:00:56 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// closes the standard input (STDIN_FILENO)
// and sets a global variable g_exit_val to 130
void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_exit_val = 130;
	}
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}

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

void	fill_heredoc(t_env *env, int fd, char *limiter)
{
	char	*buf;
	size_t	eof_len;
	int		dup_stdin;

	eof_len = ft_strlen(limiter);
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
		if (buf[0] && (eof_len == ft_strlen(buf))
			&& !ft_strncmp(limiter, buf, eof_len))
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		write(fd, "\n", 1);
		free(buf);
	}
	g_exit_val = 0;
	dup2(dup_stdin, STDIN_FILENO);
	ft_handle_signals();
	close(dup_stdin);
}

// .limiter_index_k
char	*name_heredoc(char *limiter, int index, int k)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = ft_itoa(index);
	tmp = ft_strdup(limiter);
	if (!tmp && limiter)
		return (free (tmp3), NULL);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp = ft_strjoin(tmp2, tmp3);
	free (tmp2);
	free (tmp3);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp3 = ft_itoa(k);
	tmp = ft_strjoin(tmp2, tmp3);
	free (tmp2);
	free (tmp3);
	return (tmp);
}

int	modify_limiter_nodes(t_env *env, t_lexer *lst, int index)
{
	char	*tmp;
	char	*limiter;
	int		k;

	k = 1;
	tmp = NULL;
	while (lst)
	{
		if (lst->type == LIMITER)
		{
			limiter = ft_strdup(lst->word);
			if (!limiter && lst->word)
				return (-1);
			tmp = name_heredoc(lst->word, index, k);
			if (!tmp)
				return (free (limiter), -1);
			free (lst->word);
			lst->word = ft_strjoin(".", tmp);
			free (tmp);
			create_heredoc(env, lst, limiter);
			free (limiter);
			k++;
		}
		lst = lst->next;
	}
	return (0);
}

int		init_heredocs(t_env *env, t_cmd **cmd_tab)
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

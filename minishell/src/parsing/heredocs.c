/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/14 15:44:19 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_heredoc_handler(int signum) 
{
	if (signum == SIGINT)
		close(STDIN_FILENO);
}

void signal_heredoc(void)
{
	struct sigaction	sa; 
		 
	ft_memset(&sa, 0, sizeof(sa)); 
	sa.sa_handler = &sig_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	fill_heredoc(t_lexer *lex, char *limiter)
{
	int		fd;
	char	*buf;
	size_t	eof_len;
	int		dup_stdin;

	// eof_len = ft_strlen(lex->word) - 1;
	
	eof_len = ft_strlen(limiter);
	fd = open(lex->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("could not open heredoc\n", 2),
		exit (1);// free all that is needed
	}
	dup_stdin = dup(STDIN_FILENO); // sauvegard du stdin
	signal_heredoc();
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			ft_printf("\n");
			break;
		}
		if (buf || buf[0])
		{
			if (eof_len == ft_strlen(buf) && !ft_strncmp(limiter, buf, ft_strlen(buf)))
			{
				break ;
			}
			else
			{
				ft_putstr_fd(buf, fd);
				write(fd, "\n", 1);
			}
		}
		free (buf);
	}
	close(fd);
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
	tmp3 =  ft_itoa(index);

	tmp = ft_strdup(limiter);
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

void	modify_limiter_nodes(t_lexer *lst, int index)
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
			tmp = name_heredoc(lst->word, index, k);
			free (lst->word);
			lst->word = ft_strjoin(".", tmp);
			free (tmp);
			fill_heredoc(lst, limiter);
			free (limiter);
			k++;
		}
		lst =lst->next;
	}
}

void	init_heredocs(t_cmd **cmd_tab)
{
	int		i;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
			modify_limiter_nodes(cmd_tab[i]->input, i);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/23 21:14:20 by zaquedev         ###   ########.fr       */
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

void signal_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}

void closes_heredoc(int fd, int dup_stdin)
{
	close (fd);
	close (dup_stdin);
	g_exit_val = 0;
	
}
//void	fill_heredoc(t_env *env, int fd, char *limiter)
//void	fill_heredoc(t_set *set, t_env *env, int fd, char *limiter)
// changer env pour set pour free quand le heredoc est ferme
// dup_stdin = dup(STDIN_FILENO); // sauvegard du stdin
// signal_heredoc(); // met la variable globale a 130
// ft_handle_signals(); // ignor sigquit (ctrl-\)
//void	fill_heredoc(t_cmd ***cmd_tab, t_env *env, int fd, char *limiter) 
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


//void	create_heredoc(t_cmd ***cmd_tab, t_env *env, t_lexer *lex, char *limiter)
void	create_heredoc(t_env *env, t_lexer *lex, char *limiter)
{
	int		fd;
	char	*buf;

	buf = NULL;
	fd = open(lex->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("could not open heredoc\n", 2);
		exit (1);
	}
	//fill_heredoc(cmd_tab, env, fd, limiter);
	fill_heredoc(buf , env, fd, limiter);
	close(fd);
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
	//printf("%s\n", tmp);
	return (tmp);
}


void	modify_limiter_nodes(t_env *env, t_lexer *lst, int index)
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
			create_heredoc(env, lst, limiter);
			free (limiter);
			k++;
		}
		lst = lst->next;
	}
}

//void	init_heredocs(t_env *env, t_cmd **cmd_tab)
void	init_heredocs(t_env *env, t_cmd **cmd_tab)
{
	int		i;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
		{
			//modify_limiter_nodes(&cmd_tab, env, cmd_tab[i]->input, i);
			modify_limiter_nodes(env, cmd_tab[i]->input, i);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:39:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/11 11:48:16 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_heredoc(t_lexer *lex/*, t_cmd **cmd_tab*/)
{
	int		fd;
	char	*buf;
	size_t	eof_len;

	eof_len = ft_strlen(lex->word) - 1;
	fd = open(lex->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("could not open heredoc\n", 2),
		exit (1);// free all that is needed
	}
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
			if (eof_len == ft_strlen(buf) && !ft_strncmp(&lex->word[1], buf, ft_strlen(buf)))
				break ;
			ft_putstr_fd(buf, fd);
			write(fd, "\n", 1);
		}
		free (buf);
	}
	close(fd);
}

// .limiter_index_k
char	*name_heredoc(char *eof, int index, int k)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;

	tmp = ft_strdup(lst->word);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp = ft_strjoin(tmp2, ft_itoa(index));
	free (tmp2);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp = ft_strjoin(tmp2, ft_itoa(k));
	free (tmp2);
	return (tmp);
}

void	modify_limiter_nodes(t_lexer *lst, int index)
{
	char	*tmp;
	int		k;

	k = 1;
	tmp = NULL;
	while (lst)
	{
		if (lst->type == LIMITER)
		{
			tmp = name_heredoc(lst->word, index, k);
			free (lst->word);
			lst->word = ft_strjoin(".", tmp);
			free (tmp);
			fill_heredoc(lst);
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
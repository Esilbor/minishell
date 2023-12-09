/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:13:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/09 00:44:59 by esilbor          ###   ########.fr       */
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

void	modify_limiter_nodes(t_lexer *lst)
{
	char	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (lst->type == LIMITER)
		{
			tmp = ft_strdup(lst->word);
			free (lst->word);
			lst->word = ft_strjoin(".", tmp);
			free (tmp);
			fill_heredoc(lst);
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
			modify_limiter_nodes(cmd_tab[i]->input);
		i++;
	}
}

void	invalid_input(char *filename)
{
	ft_putstr_fd("Candy_$hell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
}

void	inputs_are_valid(t_cmd **cmd_tab)
{
	int		i;
	t_lexer	*lst;
	int		fd;

	i = 0;
	lst = NULL;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
		{
			lst = cmd_tab[i]->input;
			while (lst)
			{
				fd = open(lst->word, O_RDONLY);
				if (fd < 0)
					invalid_input(lst->word);
				lst = lst->next;
				close (fd);
			}
		}
		i++;
	}
}
void	keep_last_input(t_cmd **cmd_tab)
{
	int	i;
	t_lexer *lex;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
		{
			lex = cmd_tab[i]->input;
			while (lex && lex->next)
			{
				if (unlink(lex->word) != 0)
					perror("error deleting file");
				lex = ft_remove_lex_node(&lex, lex);
				lex = lex->next;
			}
			cmd_tab[i]->input = lex;
			// free (lex); // ???
		}
		i++;
	}
}
bool outputs_are_valid(t_lexer *lex)
{
	int	fd;

	if (lex->type == APPEND)
		fd = open(lex->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(lex->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (false);
	return (true);
}

void	keep_last_output(t_cmd **cmd_tab)
{
	int		i;
	t_lexer *lex;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->output)
		{
			lex = cmd_tab[i]->output;
			while (lex && lex->next)
			{
				if(!outputs_are_valid(lex))
					exit (1);
				lex = ft_remove_lex_node(&lex, lex);
				lex = lex->next;
			}
			cmd_tab[i]->output = lex;
			// free (lex); // ???
		}
		i++;
	}
}

void	parse_input_redir(t_cmd **cmd_tab)
{
	init_heredocs(cmd_tab);
	inputs_are_valid(cmd_tab);
	keep_last_input(cmd_tab);
	keep_last_output(cmd_tab);
	// delete heredoc at the end of exec
	//keep only last input_redir per command
}


int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{

		parsing(input, lexer, envb);
		if (!(*lexer))
			return (add_history(input), 1); //>> GO TO EXIT D
		*cmd_tab = command_builder(lexer);
		parse_input_redir(*cmd_tab);
		// ft_print_struct_tab(*cmd_tab);
		free_lexer_list(lexer);
		return (0);
}

/*
EXIT D has no lexer or cmd_tab but should free input, envb 

*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:13:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/11 09:43:07 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{

		parsing(input, lexer, envb);
		if (!(*lexer))
			return (add_history(input), 1);
		*cmd_tab = command_builder(lexer);
		init_heredocs(*cmd_tab);
		inputs_are_valid(*cmd_tab);
		keep_last_input(*cmd_tab);
		keep_last_output(*cmd_tab);
		free_lexer_list(lexer);
		return (0);
}
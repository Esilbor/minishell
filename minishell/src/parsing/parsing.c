/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:13:29 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/10 12:28:27 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_input(char *filename)
{
	ft_putstr_fd("Candy_$hell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	inputs_are_valid(t_cmd **cmd_tab)
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
					return (invalid_input(lst->word));
				lst = lst->next;
				close (fd);
			}
		}
		i++;
	}
	return (0);
}

void	keep_last_input(t_cmd **cmd_tab)
{
	int		i;
	t_lexer	*lex;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->input)
		{
			lex = cmd_tab[i]->input;
			while (lex && lex->next)
			{
				if (lex->type == LIMITER)
				{
					if (unlink(lex->word) != 0)
						perror("error deleting file");
				}
				lex = ft_remove_lex_node(&lex, lex);
			}
			cmd_tab[i]->input = lex;
		}
		i++;
	}
}

// working
// void	keep_last_input(t_cmd **cmd_tab)
// {
// 	int		i;
// 	t_lexer	*lex;

// 	i = 0;
// 	while (cmd_tab[i])
// 	{
// 		if (cmd_tab[i]->input)
// 		{
// 			lex = cmd_tab[i]->input;
// 			while (lex && lex->next)
// 			{
// 				if (unlink(lex->word) != 0)
// 					perror("error deleting file");
// 				lex = ft_remove_lex_node(&lex, lex);
// 			}
// 			cmd_tab[i]->input = lex;
// 		}
// 		i++;
// 	}
// }

//not working
// void	keep_last_input(t_cmd **cmd_tab)
// {
// 	int		i;
// 	t_lexer	*lex;

// 	i = 0;
// 	while (cmd_tab[i])
// 	{
// 		if (cmd_tab[i]->input)
// 		{
// 			lex = cmd_tab[i]->input;
// 			while (lex && lex->next)
// 			{
// 				if (lex->type == LIMITER)
// 				{
// 					if (unlink(lex->word) != 0)
// 						perror("error deleting file");
// 					lex = ft_remove_lex_node(&lex, lex);
// 				}
// 				lex = lex->next;
// 			}
// 			cmd_tab[i]->input = lex;
// 		}
// 		i++;
// 	}
// }

bool	outputs_are_valid(t_lexer *lex)
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
	t_lexer	*lex;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i]->output)
		{
			lex = cmd_tab[i]->output;
			while (lex && lex->next)
			{
				if (!outputs_are_valid(lex))
					exit (1);
				lex = ft_remove_lex_node(&lex, lex);
			}
			cmd_tab[i]->output = lex;
		}
		i++;
	}
}

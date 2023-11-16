/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:19:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/16 19:25:41 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_print_struct_tab(t_cmd **struct_tab)
{
	int i;

	i = 0;
	if (!struct_tab)
	{
		ft_printf("struct_tab is NULL\n");
		return;
	}

	while (struct_tab[i])
	{
		if (!struct_tab[i]) // Null check for each element
		{
			ft_printf(RED"struct_tab[%d] is NULL\n"RESET, i);
			i++;
			continue;
		}

		ft_printf(PINK"\n********index = %d ********\n"RESET, i);
		ft_printf("\n\n");

		if (struct_tab[i]->cmd[0])
		{
			ft_printf(GREEN"CMD[%d]\n", i);
			ft_print_tab((void **)struct_tab[i]->cmd, "cmd");
			ft_printf("***************\n\n"RESET);
		}

		if (struct_tab[i]->eof[0])
		{
			ft_printf(BLUE"HEREDOC[%d]\n", i);
			ft_print_tab((void **)struct_tab[i]->eof, "eof");
			ft_printf("***************\n\n"RESET);
		}

		if (struct_tab[i]->input_redir[0])
		{
			ft_printf(CYAN"INPUT_TAB[%d]\n", i);
			ft_print_tab((void **)struct_tab[i]->input_redir, "input");
			ft_printf("***************\n\n"RESET);
		}

		if (struct_tab[i]->output_redir[0])
		{
			ft_printf(YELLOW"OUTPUT_TAB[%d]\n", i);
			ft_print_tab((void **)struct_tab[i]->output_redir, "output");
			ft_printf("***************\n\n"RESET);
		}

		i++;
	}
}
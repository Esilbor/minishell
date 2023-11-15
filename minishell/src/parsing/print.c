/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:19:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/15 22:31:02 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_print_struct_tab(t_cmd	**struct_tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!struct_tab)
// 		return ;
// 	while (struct_tab[i])
// 	{
// 		ft_printf("\n***index = %d ***\n", i);
// 		ft_printf("***************\n\n");
// 		if (struct_tab[i]->cmd)
// 		{
// 			ft_printf("CMD[%d]\n", i);
// 			ft_print_tab((void **)struct_tab[i]->cmd, "cmd");
// 			ft_printf("***************\n\n");
// 		}
// 		if (struct_tab[i]->eof)
// 		{
// 			ft_printf("EOF[%d]\n", i);
// 			ft_print_tab((void **)struct_tab[i]->eof, "eof");
// 			ft_printf("***************\n\n");
// 		}
// 		if (struct_tab[i]->input_redir)
// 		{
// 			ft_printf("INPUT_TAB[%d]\n", i);
// 			ft_print_tab((void **)struct_tab[i]->input_redir, "input");
// 			ft_printf("***************\n\n");
// 		}
// 		if (struct_tab[i]->output_redir)
// 		{
// 			ft_printf("OUTPUT_TAB[%d]\n", i);
// 			ft_print_tab((void **)struct_tab[i]->output_redir, "output");
// 			ft_printf("***************\n\n");
// 		}
// 		i++;
// 	}
// }

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
            ft_printf("struct_tab[%d] is NULL\n", i);
            i++;
            continue;
        }

        ft_printf("\n***index = %d ***\n", i);
        ft_printf("***************\n\n");

        if (struct_tab[i]->cmd)
        {
            ft_printf("CMD[%d]\n", i);
            ft_print_tab((void **)struct_tab[i]->cmd, "cmd");
            ft_printf("***************\n\n");
        }

        if (struct_tab[i]->eof)
        {
            ft_printf("HEREDOC[%d]\n", i);
            ft_print_tab((void **)struct_tab[i]->eof, "eof");
            ft_printf("***************\n\n");
        }

        if (struct_tab[i]->input_redir)
        {
            ft_printf("INPUT_TAB[%d]\n", i);
            ft_print_tab((void **)struct_tab[i]->input_redir, "input");
            ft_printf("***************\n\n");
        }

        if (struct_tab[i]->output_redir)
        {
            ft_printf("OUTPUT_TAB[%d]\n", i);
            ft_print_tab((void **)struct_tab[i]->output_redir, "output");
            ft_printf("***************\n\n");
        }

        i++;
    }
}

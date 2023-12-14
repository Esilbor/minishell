/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:19:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/14 08:01:52 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*******************************************************************/
/******************PRINT FUNCTIONS *********************************/
/*******************************************************************/
/*******************************************************************/

// char	*print_token(t_tokens token)
// {
// 	if (token == WORD)
// 		return ("WORD");
// 	else if (token == PIPE)
// 		return ("PIPE");
// 	else if (token == LESS)
// 		return ("LESS");
// 	else if (token == GREAT)
// 		return ("GREAT");
// 	else if (token == LESS_LESS)
// 		return ("LESS_LESS");
// 	else if (token == GREAT_GREAT)
// 		return ("GREAT_GREAT");
// 	else if (token == DOLLAR)
// 		return ("DOLLAR");
// 	else if (token == DQUOTE)
// 		return ("DQUOTE");
// 	else if (token == SQUOTE)
// 		return ("SQUOTE");
// 	else if (token == EXPAND)
// 		return ("EXPAND");
// 	else if (token == LIMITER)
// 		return ("LIMITER");
// 	else if (token == INPUT)
// 		return ("INPUT");
// 	else if (token == OUTPUT)
// 		return ("OUTPUT");
// 	else if (token == APPEND)
// 		return ("APPEND");
// 	else if (token == SMERGE)
// 		return ("SMERGE");
// 	else if (token == DMERGE)
// 		return ("DMERGE");
// 	else if (token == WMERGE)
// 		return ("WMERGE");
// 	else if (token == EMERGE)
// 		return ("EMERGE");
// 	return ("ERROR");
// }

// void	print_lexer(t_lexer **head, char *loc)
// {
// 	t_lexer	*lst;
// 	int		i;

// 	lst = *head;
// 	i = 0;
// 	ft_printf(PINK"\n%s\n"RESET, loc);
// 	ft_printf(WHITE"CMD[%d] = ", i++);
// 	while (lst)
// 	{
// 		if (lst->type == WORD)
// 			ft_printf(GREEN"[%s__WORD__]"RESET, lst->word);
// 		else if (lst->type == PIPE)
// 		{
// 			ft_printf(PINK"[%s__PIPE__]"RESET, lst->word);
// 			ft_printf("\n\n");
// 			ft_printf(WHITE"CMD[%d] = ", i++);
// 		}
// 		else if (lst->type == LIMITER)
// 			ft_printf(BLUE"[%s__LIMITER__]"RESET, lst->word);
// 		else if (lst->type == INPUT)
// 			ft_printf(CYAN"[%s__INPUT__]"RESET, lst->word);
// 		else if (lst->type == OUTPUT)
// 			ft_printf(YELLOW"[%s__OUTPUT__]"RESET, lst->word);
// 		else if (lst->type == APPEND)
// 			ft_printf(YELLOW"[%s__APPEND__]"RESET, lst->word);
// 		else if (lst)
// 			ft_printf(RED"[%s__%s]"RESET, lst->word, print_token(lst->type));
// 		lst = lst->next;
// 	}
// 	ft_printf("\n");
// }

// Print the contents of the struct_tab array // TO BE DELETED
// void	ft_print_struct_tab(t_cmd **struct_tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!struct_tab)
// 	{
// 		ft_printf("struct_tab is NULL\n");
// 		return ;
// 	}
// 	while (struct_tab[i])
// 	{
// 		if (!struct_tab[i])
// 		{
// 			ft_printf(RED"struct_tab[%d] is NULL\n"RESET, i);
// 			i++;
// 			continue ;
// 		}
// 		ft_printf(PINK"\n********index = %d ********\n"RESET, i);
// 		ft_printf("\n\n");
// 		if (struct_tab[i]->cmd[0])
// 		{
// 			ft_printf(GREEN"CMD[%d]\n", i);
// 			ft_print_tab((void **)struct_tab[i]->cmd, "cmd");
// 			ft_printf("***************\n\n"RESET);
// 		}
// 		if (struct_tab[i]->output)
// 		{
// 			ft_printf(YELLOW"OUTPUT_LST[%d]\n", i);
// 			print_lexer(&(struct_tab[i])->output, "out");
// 			ft_printf("***************\n\n"RESET);
// 		}
// 		if (struct_tab[i]->input)
// 		{
// 			ft_printf(CYAN"INPUT_LST[%d]\n", i);
// 			print_lexer(&(struct_tab[i])->input, "in");
// 			ft_printf("***************\n\n"RESET);
// 		}
// 		i++;
// 	}
// }

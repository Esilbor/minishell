/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:55:46 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/03 16:18:45 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// void	ft_get_input(char **input, int exit_status)
// {
// 	static char	rps[] = {RL_PROMPT_START_IGNORE, '\0'};
// 	static char	rpe[] = {RL_PROMPT_END_IGNORE, '\0'};
// 	char		*arrow_color;
// 	char		*prompt;

// 	if (isatty(0))
// 	{
// 		if (!exit_status)
// 			arrow_color = GREEN;
// 		else
// 			arrow_color = RED;
// 		prompt = ft_strsjoin((char *[]){
// 				rps, BOLD, arrow_color, rpe,
// 				TASH_PROMPT, rps, CYAN, rpe,
// 				PROMPT, rps, RESET, rpe, " ", NULL});
// 		if (prompt)
// 			*input = readline(prompt);
// 		else
// 			*input = readline(PROMPT);
// 		free(prompt);
// 	}
// 	else
// 		*input = ft_get_next_line(0);
// }

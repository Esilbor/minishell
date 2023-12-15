/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:04:09 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/15 19:18:08 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{
	parsing(input, lexer, envb);
	if (!(*lexer))
		return (add_history(input), 1);
	*cmd_tab = command_builder(lexer);
	init_heredocs(envb, *cmd_tab);
	if (inputs_are_valid(*cmd_tab) == 1)
	{
		free_cmd_struct_tab(*cmd_tab);
		free_lexer_list(lexer);
		return (add_history(input), 1);
	}
	keep_last_input(*cmd_tab);
	keep_last_output(*cmd_tab);
	free_lexer_list(lexer);
	// if (cmd_tab[0][0]->cmd[0])
	// {
	// 	ft_printf("dans shell_parser\n");
	// 	return (1);
	// }
	return (0);
}

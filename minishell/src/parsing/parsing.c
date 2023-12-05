/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:13:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/05 19:01:10 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_heredoc_path(t_cmd **cmd_tab, int index)
// {
// 	char	*name;

// 	name = cmd_tab[index]->eof
// }

// int	create_heredoc(t_cmd **cmd_tab, /* char *file_name, */ int index/* , int fd */)
// {

// }

// void	parse_input_redir(t_cmd **cmd_tab)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_tab[i]->eof)
// 	{
// 		create_heredoc_path(cmd_tab, i);
// 		create_heredoc(cmd_tab, i);
// 	}

// 	//keep only last input_redir per command
// }

int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{

		parsing(input, lexer, envb);
		if (!(*lexer))
			return (add_history(input), 1);
		print_lexer(lexer, "before command_builder");
		*cmd_tab = command_builder(lexer);
		// parse_input_redir(*cmd_tab); //
		// ft_print_struct_tab(*cmd_tab);
		free_lexer_list(lexer);
		return (0);
}

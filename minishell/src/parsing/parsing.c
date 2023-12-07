/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:13:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/07 10:07:01 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_heredoc_path(t_cmd **cmd_tab, int index)
{
	char	*name;
	t_lexer	*lst;

	lst = cmd_tab[index]->input;
	while (lst)
	{
		if (lst->type == APPEND)
		{
			name = ft_strjoin(".heredoc_", lst->word);
		}
	}

	name = cmd_tab[index]->eof
}

int	fill_heredoc(t_cmd **cmd_tab, /* char *file_name, */ int index/* , int fd */)
{

}

void	init_heredoc_path(t_cmd **cmd_tab)
{
	t_lexer	*lst;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	while (cmd_tab[i])
	
	{
		while (cmd_tab[i]->input)
		{
			lst = cmd_tab[i]->input;
			if (lst->type == APPEND)
				j++;
			lst = lst->next;
		}
		i++;
	}
	cmd_tab
}

void	parse_input_redir(t_cmd **cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i]->eof)
	{
		init_heredoc_path(cmd_tab);
		create_heredoc_path(cmd_tab, i);
		fill_heredoc(cmd_tab, i);
	}

	//keep only last input_redir per command
}

int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{

		parsing(input, lexer, envb);
		if (!(*lexer))
			return (add_history(input), 1);
		*cmd_tab = command_builder(lexer);
		parse_input_redir(*cmd_tab); //
		ft_print_struct_tab(*cmd_tab);
		free_lexer_list(lexer);
		return (0);
}

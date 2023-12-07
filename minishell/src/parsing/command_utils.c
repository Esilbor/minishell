/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/05 15:40:21 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Count the number of commands in the lexer list
int	count_cmd(t_lexer *lex)
{
	int	i;

	i = 0;
	if (lex)
		i = 1;
	while (lex)
	{
		if (lex->type == PIPE)
			i ++;
		lex = lex->next;
	}
	return (i);
}

// Initialize an array of command structures from lexer
t_cmd	**init_cmd_struct(t_lexer **lexer)
{
	t_cmd	**cmd_struct_tab;
	int		cmd_nb;
	int		i;

	i = 0;
	cmd_nb = count_cmd(*lexer);
	cmd_struct_tab = malloc(sizeof(t_cmd *) * (cmd_nb + 1));
	if (!cmd_struct_tab)
		return (NULL);
	while (i < cmd_nb)
	{
		cmd_struct_tab[i] = malloc(sizeof (t_cmd));
		if (!cmd_struct_tab[i])
			return (ft_free_tab((void **)cmd_struct_tab), NULL);
		ft_memset(cmd_struct_tab[i], 0, sizeof(t_cmd));
		// cmd_struct_tab[i]->output = NULL;
		// cmd_struct_tab[i]->input = NULL;
		i ++;
	}
	if (i)
		cmd_struct_tab[i] = NULL;
	return (cmd_struct_tab);
}

// need to send the pointer to the given lexer node
// count the nb of a specific token in a given command
int	token_nb(t_lexer **lexer, t_tokens token)
{
	t_lexer	*lex;
	int		tok_nb;

	lex = *lexer;
	tok_nb = 0;
	if (token == PIPE)
		return (count_cmd(lex));
	while (lex && lex->type != PIPE)
	{
		if (lex->type == token)
			tok_nb++;
		lex = lex->next;
	}
	return (tok_nb);
}

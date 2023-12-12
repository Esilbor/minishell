/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/10 14:53:01 by esilbor          ###   ########.fr       */
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

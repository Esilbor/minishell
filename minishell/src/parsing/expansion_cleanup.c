/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:51:44 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/20 09:51:53 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_lexer4(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type >= EXPAND && lex->type <= EMERGE)
			lex->type = WORD;
		lex = lex->next;
	}
}

//Processes lexer tokens, removing << < > and >> types from the list.
void	clean_lexer3(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS_LESS || lex->type == LESS
			|| lex->type == GREAT || lex->type == GREAT_GREAT)
		{
			lex = ft_remove_lex_node(lexer, lex);
		}
		if (lex->type == EXPAND && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		if (lex->type == WORD && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
}

//Processes lexer tokens, setting limiter and append types.
void	clean_lexer2(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS_LESS
			&& (lex->next->type == WORD || lex->next->type == EXPAND))
			clean_redir(lexer, &lex, LIMITER);
		else if (lex->type == GREAT_GREAT && (lex->next->type == WORD
				|| lex->next->type == EXPAND))
			clean_redir(lexer, &lex, APPEND);
		if (lex)
			lex = lex->next;
	}
}

//Processes lexer tokens, setting input/output types.
void	clean_lexer(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS && (lex->next->type == WORD
				|| lex->next->type == EXPAND))
			clean_redir(lexer, &lex, INPUT);
		else if (lex->type == GREAT && (lex->next->type == WORD
				|| lex->next->type == EXPAND))
			clean_redir(lexer, &lex, OUTPUT);
		if (lex)
			lex = lex->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:51:44 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/28 17:50:04 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Processes lexer tokens, removing << < > and >> types from the list.
void	clean_lexer3(t_lexer **lexer)
{
	t_lexer	*lex;
	// print_lexer(lexer, "before clean_lexer3()");

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS_LESS || lex->type == LESS
			|| lex->type == GREAT || lex->type == GREAT_GREAT)
		{
			if (lex->next->type == APPEND || lex->next->type == LIMITER
				||lex->next->type == OUTPUT || lex->next->type == INPUT)
			{
				syntax_error(lex, lexer);
				return ; //echo a>>>b|ls
			}
			lex = ft_remove_lex_node(lexer, lex);
		}
		if (lex->type == EXPAND && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		if (lex->type == WORD && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
	// print_lexer(lexer, "after clean_lexer3()");

}

// clean and attribute nodes of type LIMITER, APPEND, INPUT or OUTPUT
void	clean_redir(t_lexer **lexer, t_lexer **lex, t_tokens type)
{
	t_tokens	token;

	token = type - 7;
	if (token <= 1)
	{
		ft_putstr_fd("invalid clean_redir type\n", 2);
		return ;
	}
	if ((*lex)->type >= PIPE && (*lex)->type <= LESS_LESS)
		*lex = ft_remove_lex_node(lexer, *lex);
    *lex = (*lex)->next;
	if (!(*lex)->word[0])
	{
		*lex = ft_remove_lex_node(lexer, *lex);
		*lex = (*lex)->next;
	}
	if (*lex)
		(*lex)->type = type;
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
	clean_lexer3(lexer);
}

void	clean_squotes(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == SQUOTE || lex->type == SMERGE)
			lex = clean_quotes(lex);
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
	clean_lexer2(lexer);
}

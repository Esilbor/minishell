/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:17:32 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/14 07:28:27 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		*lex = (*lex)->next;
	if (*lex && !(*lex)->word[0])
	{
		*lex = ft_remove_lex_node(lexer, *lex);
		*lex = (*lex)->next;
	}
	if (*lex)
		(*lex)->type = type;
}

// remove \ pointed by esc from lex->word
void	clean_esc(t_lexer **lex, char **esc)
{
	char	*before;
	char	*after;

	before = ft_strpcpy((*lex)->word, *esc);
	after = ft_strdup(*esc + 1);
	free ((*lex)->word);
	(*lex)->word = ft_strjoin(before, after);
	*esc = ft_strchr((*lex)->word, '\\');
	free (before);
	free (after);
}

//clean the lexer of null nodes of type WORD
t_lexer	**clean_empty_nodes(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == WORD && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
	return (lexer);
}

//finally change SQUOTES and DQUOTES into WORDS before cleaning
void	quotes_to_words(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == SQUOTE || lex->type == DQUOTE)
			lex->type = WORD;
		lex = lex->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_spec_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:09:01 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/21 14:24:07 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Detects shell symbols (|, <, >, $, >>, <<), defaults to WORD
t_tokens	is_spec_char3(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '$')
		return (DOLLAR);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	return (WORD);
}

// Detects shell symbols (|, <, >, >>, <<, quotes), defaults to WORD
t_tokens	is_spec_char2(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (*c == '"')
		return (DQUOTE);
	else if (*c == '\'')
		return (SQUOTE);
	return (WORD);
}

// Detects shell symbols (|, <, >, >>, <<, quotes, $), defaults to WORD
t_tokens	is_spec_char(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '$')
		return (DOLLAR);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (*c == '"')
		return (DQUOTE);
	else if (*c == '\'')
		return (SQUOTE);
	return (WORD);
}

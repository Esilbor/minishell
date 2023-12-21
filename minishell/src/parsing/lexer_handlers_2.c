/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:05:48 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/21 19:19:37 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_non_quote(char *str, int *i, int *j, char *epur_str)
{
	while (str[*i] && !is_wspace(str[*i]) && !is_quote(str[*i]))
		epur_str[(*j)++] = str[(*i)++];
	if (str[*i] && !str[*i + 1])
		(*i)++;
	while (is_wspace(str[*i]) && is_wspace(str[*i + 1]))
		(*i)++;
	if (str[*i] && str[*i + 1] && !is_quote(str[*i]) && is_wspace(str[*i]))
		epur_str[(*j)++] = str[(*i)++];
}

void	handle_quote(char *str, int *i, int *j, char *epur_str)
{
	char	quote_char;

	quote_char = str[*i];
	if (str[*i] && str[*i + 1] && str[*i + 1] == quote_char)
	{
		// *i += 2; // croc
		epur_str[(*j)++] = str[(*i)++];
	}
	if (str[*i])
	{
		epur_str[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != quote_char)
			epur_str[(*j)++] = str[(*i)++];
		if (str[*i] == quote_char)
			epur_str[(*j)++] = str[(*i)++];
	}
}

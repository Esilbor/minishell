/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:05:48 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/04 05:23:03 by esilbor          ###   ########.fr       */
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

// Process words with special chars in cmd_line
void	handle_words_spec_char(char *str, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (str[j] && !is_spec_char(&str[j]) && str[j] != ' ' && str[j] != '$')
		j++;
	if (str[j] && str[j] != ' ' && (!is_spec_char4(&str[j]) || str[j] == '$'))
	{
		tmp = ft_strndup(&str[*i], j - *i);
		ft_add_lex_node(head, tmp, WMERGE);
		free(tmp);
	}
	else if (!str[j] || str[j] == ' ' || is_spec_char4(&str[j]))
	{
		tmp = ft_strndup(&str[*i], j - *i);
		ft_add_lex_node(head, tmp, WORD);
		free(tmp);
		if (str[j] == ' ' && (str[j + 1] == '\'' || str[j + 1] == '\"'))
			ft_add_lex_node(head, "", QSPACE);
	}
	if (is_spec_char3(&str[j]))
		handle_spec_chars(str, &j, head);
	*i = j;
}

void	free_lexer_list(t_lexer **head)
{
	t_lexer	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->word);
		free(tmp);
	}
}

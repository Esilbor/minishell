/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:02:57 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 10:16:17 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handles single quotes in 'cmd_line', adds to lexer list, checks for errors
int	handle_squotes(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (cmd_line[j] && cmd_line[j] != '\'')
		j++;
	if (!cmd_line[j])
	{
		ft_putstr_fd("Candy_$hell: syntax error: unclosed Squote\n", 2);
		*i = j;
		return (1);
	}
	tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
	if (cmd_line[j + 1] && cmd_line[j + 1] != ' '
		&& !is_spec_char4(&cmd_line[j + 1]))
		ft_add_lex_node(head, tmp, SMERGE);
	else
	{
		ft_add_lex_node(head, tmp, SQUOTE);
		ft_add_lex_node(head, "", QSPACE);
	}
	free(tmp);
	*i = j + 1;
	return (0);
}

int	handle_dquotes(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (cmd_line[j] && cmd_line[j] != '\"')
		j++;
	if (!cmd_line[j])
	{
		ft_putstr_fd("Candy_$hell: syntax error: unclosed Dquote\n", 2);
		*i = j;
		return (1);
	}
	tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
	if (cmd_line[j + 1] && cmd_line[j + 1] != ' ')
	{
		ft_add_lex_node(head, tmp, DMERGE);
	}
	else
	{
		ft_add_lex_node(head, tmp, DQUOTE);
		ft_add_lex_node(head, "", QSPACE);
	}
	free(tmp);
	*i = j + 1;
	return (0);
}

// Processes double quotes in 'cmd_line', updates lexer, handles syntax errors
void	handle_spec_chars(char *epur_line, int *j, t_lexer **head)
{
	char	*tmp;

	if ((is_spec_char(&epur_line[*j]) == LESS_LESS
			|| is_spec_char(&epur_line[*j]) == GREAT_GREAT)
		&& epur_line[*j + 1])
	{
		tmp = ft_strndup(&epur_line[*j], 2);
		ft_add_lex_node(head, tmp, is_spec_char(&epur_line[*j]));
		free(tmp);
		*j += 2;
	}
	else if (is_spec_char(&epur_line[*j]) == DOLLAR && epur_line[*j + 1]
		&& epur_line[*j + 1] != ' ')
		handle_dollar(epur_line, j, head);
	else
	{
		tmp = ft_strndup(&epur_line[*j], 1);
		ft_add_lex_node(head, tmp, is_spec_char2(&epur_line[*j]));
		free(tmp);
		(*j)++;
	}
}

void	handle_dollar(char *epur_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = *i;
	while (epur_line[j] && !is_spec_char2(&epur_line[j]) && epur_line[j] != ' ')
		j++;
	tmp2 = ft_strndup(&epur_line[*i], j - *i);
	if (epur_line[j] && !dol_to_expand(tmp2))
	{
		tmp = ft_strndup("\0", 2);
		ft_add_lex_node(head, tmp, WMERGE);
	}
	else if (epur_line[j] && epur_line[j] != ' '
		&& is_spec_char2(&epur_line[j]))
	{
		tmp = ft_strndup(&epur_line[*i], j - *i);
		ft_add_lex_node(head, tmp, EMERGE);
	}
	else if (!epur_line[j] || epur_line[j] == ' '
		|| is_spec_char2(&epur_line[j]))
	{
		tmp = ft_strndup(&epur_line[*i], j - *i);
		ft_add_lex_node(head, tmp, EXPAND);
	}
	free(tmp);
	free(tmp2);
	*i = j;
}

// Process words with special chars in cmd_line
void	handle_words_spec_char(char *epur_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (epur_line[j] && !is_spec_char(&epur_line[j])
		&& epur_line[j] != ' ' && epur_line[j] != '$')
		j++;
	if (epur_line[j] && epur_line[j] != ' ' && (!is_spec_char4(&epur_line[j])
			|| epur_line[j] == '$'))
	{
		tmp = ft_strndup(&epur_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WMERGE);
		free(tmp);
	}
	else if (!epur_line[j] || epur_line[j] == ' '
		|| is_spec_char4(&epur_line[j]))
	{
		tmp = ft_strndup(&epur_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WORD);
		free(tmp);
		if (epur_line[j] == ' ' && (epur_line[j + 1] == '\''
				|| epur_line[j + 1] == '\"'))
			ft_add_lex_node(head, "", QSPACE);
	}
	if (is_spec_char3(&epur_line[j]))
		handle_spec_chars(epur_line, &j, head);
	*i = j;
}

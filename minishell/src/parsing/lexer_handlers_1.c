/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:02:57 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/05 17:53:40 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

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
		&& !is_spec_char3(&cmd_line[j + 1]))
		ft_add_lex_node(head, tmp, SMERGE);
	else
		ft_add_lex_node(head, tmp, SQUOTE);
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
		ft_add_lex_node(head, tmp, DMERGE);
	else
	{
		ft_add_lex_node(head, tmp, DQUOTE);
		ft_add_lex_node(head, "", QSPACE);
	}
		// ft_add_lex_node(head, tmp, DQUOTE);
	free(tmp);
	*i = j + 1;
	return (0);
}

// Processes double quotes in 'cmd_line', updates lexer, handles syntax errors
void	handle_spec_chars(char *cmd_line, int *j, t_lexer **head)
{
	char	*tmp;

	if ((is_spec_char(&cmd_line[*j]) == LESS_LESS
			|| is_spec_char(&cmd_line[*j]) == GREAT_GREAT) && cmd_line[*j + 1])
	{
		tmp = ft_strndup(&cmd_line[*j], 2);
		ft_add_lex_node(head, tmp, is_spec_char(&cmd_line[*j]));
		free(tmp);
		*j += 2;
	}
	else if (is_spec_char(&cmd_line[*j]) == DOLLAR && cmd_line[*j + 1]
		&& cmd_line[*j + 1] != ' ')
		handle_dollar(cmd_line, j, head);
	else
	{
		tmp = ft_strndup(&cmd_line[*j], 1);
		ft_add_lex_node(head, tmp, is_spec_char2(&cmd_line[*j]));
		free(tmp);
		(*j)++;
	}
}

void	handle_dollar(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (cmd_line[j] && !is_spec_char2(&cmd_line[j]) && cmd_line[j] != ' ')
		j++;
	if (cmd_line[j] && cmd_line[j] != ' ' && is_spec_char2(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, EMERGE);
		free(tmp);
	}
	else if (!cmd_line[j] || cmd_line[j] == ' ' || is_spec_char2(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, EXPAND);
		free(tmp);
	}
	*i = j;
}

// Process words with special chars in cmd_line
void	handle_words_spec_char(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (cmd_line[j] && !is_spec_char(&cmd_line[j]) && cmd_line[j] != ' ')
		j++;
	if (cmd_line[j] && cmd_line[j] != ' ' && !is_spec_char4(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WMERGE);
		free(tmp);
	}
	else if (!cmd_line[j] || cmd_line[j] == ' ' || is_spec_char3(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WORD);
		free(tmp);
	}
	if (is_spec_char3(&cmd_line[j]))
		handle_spec_chars(cmd_line, &j, head);
	*i = j;
}
*/

/*

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

	tmp =NULL;
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
*/

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

static void	add_empty_wmerge(t_lexer **lexer)
{
	char	*tmp;

	tmp = ft_strndup("\0", 2);
	ft_add_lex_node(lexer, tmp, WMERGE);
	free (tmp);
}

int	handle_dollar(char *str, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = *i;
	tmp = NULL;
	while (str[j] && !is_spec_char2(&str[j]) && str[j] != ' ')
		j++;
	tmp2 = ft_strndup(&str[*i], j - *i);
	if (str[j] && !dol_to_expand(tmp2))
		add_empty_wmerge(head);
	else if (str[j] && str[j] != ' ' && is_spec_char2(&str[j]))
	{
		tmp = ft_strndup(&str[*i], j - *i);
		ft_add_lex_node(head, tmp, EMERGE);
	}
	else if (!str[j] || str[j] == ' ' || is_spec_char2(&str[j]))
	{
		tmp = ft_strndup(&str[*i], j - *i);
		ft_add_lex_node(head, tmp, EXPAND);
	}
	*i = j;
	return (free(tmp), free(tmp2), 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:14:20 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/30 18:07:55 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// return 1 if c is a space or a tab else 0
int	is_wspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// return 1 if char c is a single or double quote
int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_epur_str(char *str)
{
	int		i;
	int		j;
	char	*epur_str;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	epur_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!epur_str)
		return (NULL);
	while (str[i])
	{
		while (is_wspace(str[i]) && is_wspace(str[i + 1]))
			i++;
		if (is_quote(str[i]))
			handle_quote(str, &i, &j, epur_str);
		else
			handle_non_quote(str, &i, &j, epur_str);
	}
	epur_str[j] = '\0';
	if (epur_str[0])
		return (epur_str);
	free (epur_str);
	return (NULL);
}

void	handle_space(char *epur_line, int *i, t_lexer **head)
{
	char	*tmp;

	tmp = ft_strndup(&epur_line[*i], 1);
	ft_add_lex_node(head, tmp, ISSPACE);
	free (tmp);
	(*i)++;
}

// Fill lexer list from cmd_line string
int	ft_fill_lexer(t_lexer **lexer, char *epur_line)
{
	int		i;
	t_lexer	*head;

	i = 0;
	head = *lexer;
	while (epur_line[i])
	{
		if (epur_line[i] == '\"')
		{
			if (handle_dquotes(epur_line, &i, &head))
				return (*lexer = head, 1);
		}
		else if (epur_line[i] == '\'')
		{
			if (handle_squotes(epur_line, &i, &head))
				return (*lexer = head, 1);
		}
		else
			handle_words_spec_char(epur_line, &i, &head);
		while (epur_line[i] && epur_line[i] == ' ')
			i++;
	}
	*lexer = head;
	return (0);
}

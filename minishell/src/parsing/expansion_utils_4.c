/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:56:59 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 18:10:16 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	clean_space_nodes2(t_lexer **lexer)
{
	t_lexer	*lex;
	char	*tmp;
	t_lexer	*previous;
	int		i;

	previous = *lexer;
	lex = *lexer;
	i = 0;
	while (lex)
	{
		if (quote_is_space(lex) < 0 && i > 1)
		{
			tmp = ft_strdup(previous->word);
			if (!tmp && previous->word)
				return (free(tmp), free_lexer_list(lexer), 1);
			free(previous->word);
			previous->word = ft_strjoin(tmp, " ");
			free (tmp);
			lex = lex->next;
		}
		previous = lex;
		lex = lex->next;
		i++;
	}
	return (0);
}

int	quote_is_space(t_lexer *lex)
{
	if (lex->type == QSPACE && lex->next && lex->next->type == ISSPACE
		&& lex->next->next && lex->next->next->type == QSPACE
		&& lex->next->next->next && (lex->next->next->next->type == WORD
			|| (lex->next->next->next->type >= EXPAND
				&& lex->next->next->next->type <= EMERGE)))
		return (1);
	else if (lex->type == QSPACE && lex->next && lex->next->type == ISSPACE
		&& lex->next->next && lex->next->next->type == QSPACE
		&& (!lex->next->next->next || (lex->next->next->next->type >= PIPE
				&& lex->next->next->next->type <= LESS_LESS)))
		return (-1);
	else if (lex->type == QSPACE && lex->next && lex->next->type == ISSPACE
		&& (lex->next->next && (lex->next->next->type >= PIPE
				&& lex->next->next->type <= LESS_LESS)))
		return (-1);
	return (0);
}

void	clean_space_nodes(t_lexer **lexer)
{
	t_lexer	*lex;
	char	*tmp;
	char	*tmp2;

	lex = *lexer;
	while (lex)
	{
		if (lexer && quote_is_space(lex) == 1)
		{
			tmp = lex->next->next->next->word;
			tmp2 = ft_strjoin(" ", tmp);
			free(lex->next->next->next->word);
			lex->next->next->next->word = tmp2;
			lex = lex->next;
		}
		else if (quote_is_space(lex) < 0)
		{
			clean_space_nodes2(lexer);
		}
		if (!(*lexer))
			return ;
		lex = lex->next;
	}
}

void	lexer_polish(t_lexer **lexer)
{
	clean_squotes(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
	clean_space_nodes(lexer);
	clean_lexer2(lexer);
	clean_lexer3(lexer);
	merge_nodes(lexer);
	remove_space_nodes(lexer);
	lexer = expand_cmds(lexer);
	clean_lexer4(lexer);
	clean_empty_nodes(lexer, WORD);
}

t_lexer	*parsing(char *input, t_lexer **lexer, t_env *envb)
{
	*lexer = ft_lexer(input, envb);
	if (!(*lexer))
		return (add_history(input), NULL);
	add_history(input);
	ft_expander(lexer, envb);
	clean_empty_nodes(lexer, EXPAND);
	clean_empty_nodes(lexer, WMERGE);
	lexer_polish(lexer);
	if (!(*lexer))
		return (add_history(input), NULL);
	return (*lexer);
}

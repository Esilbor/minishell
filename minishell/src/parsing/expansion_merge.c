/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 12:53:18 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	merge_nodes(t_lexer **lexer)
{
	t_lexer	*lex;
	t_lexer	*node_to_remove;
	char	*merged_word;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type >= SMERGE && lex->type <= EMERGE
			&& !(lex->next->type >= 9 && lex->next->type <= 12))
		{
			merged_word = ft_strjoin(lex->word, lex->next->word);
			free(lex->next->word);
			lex->next->word = merged_word;
			node_to_remove = lex;
			lex = lex->next;
			if (lex == *lexer)
				*lexer = lex;
			ft_remove_lex_node(lexer, node_to_remove);
		}
		else
			lex = lex->next;
	}
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

// replace the value of expand nodes to the matching environment value
void	ft_expander(t_lexer **lexer, t_env *envb)
{
	t_lexer	*lst;
	char	*tmp;
	char	*esc;

	lst = *lexer;
	while (lst)
	{
		if (lst->type == DQUOTE || lst->type == DMERGE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_dquote(tmp, lst, envb);
			esc = ft_strchr(lst->word, '\\');
			while (esc && esc[1] != '\"' && esc[1] != '?')
				clean_esc(&lst, &esc);
			lst = clean_quotes(lst);
		}
		else if (lst->type == EXPAND || lst->type == EMERGE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_node2(tmp, lst, envb);
			esc = ft_strchr(lst->word, '\\');
			while (esc && esc[1])
				clean_esc(&lst, &esc);
		}
		lst = lst->next;
	}
}

//clean the lexer of null nodes of type WORD
t_lexer	**clean_empty_nodes(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == WORD && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
	return (lexer);
}

void	lexer_polish(t_lexer **lexer)
{
	clean_squotes(lexer);
	// print_lexer(lexer, "clean_squotes");
	quotes_to_words(lexer);
	// print_lexer(lexer, "quotes_to_words");
	clean_lexer(lexer);
	// print_lexer(lexer, "clean_lexer");
	clean_lexer2(lexer);
	// print_lexer(lexer, "clean_lexer2");
	clean_lexer3(lexer);
	// print_lexer(lexer, "clean_lexer3");
	merge_nodes(lexer);
	// print_lexer(lexer, "merge_nodes");
	clean_lexer4(lexer);
	// print_lexer(lexer, "clean_lexer4");
	clean_empty_nodes(lexer);
	// print_lexer(lexer, "clean_empty_nodes");
}

t_lexer	*parsing(char *input, t_lexer **lexer, t_env *envb)
{
	*lexer = ft_lexer(input);
	if (!(*lexer))
		return (add_history(input), NULL);
	add_history(input);
	ft_expander(lexer, envb);
	lexer_polish(lexer);
	if (!(*lexer))
		return (add_history(input), NULL);
	return (*lexer);
}


// inputs are in THE WRONG LIST!!!

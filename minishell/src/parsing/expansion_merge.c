/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/30 15:55:10 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//merge two nodes when they are of same type and next to each other
//UNUSED
void	merge_nodes(t_lexer **lexer)
{
	t_lexer	*lex;
	t_lexer	*node_to_remove;
	char	*merged_word;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type >= SMERGE && lex->type <= EMERGE)
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
	print_lexer(lexer, "before clean_squotes");
	clean_squotes(lexer);
	// print_lexer(lexer, "before merge_nodes");
	// merge_nodes(lexer);
	print_lexer(lexer, "before quotes_to_words");
	quotes_to_words(lexer);
	print_lexer(lexer, "before clean_lexer");
	clean_lexer(lexer);
	print_lexer(lexer, "before clean_lexer2");
	clean_lexer2(lexer);
	print_lexer(lexer, "before clean_lexer3");
	clean_lexer3(lexer);
	print_lexer(lexer, "before clean_lexer4");
	clean_lexer4(lexer);
	print_lexer(lexer, "after clean_lexer4");
}

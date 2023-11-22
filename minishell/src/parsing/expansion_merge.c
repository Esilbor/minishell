/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/22 23:25:58 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//merge two nodes when they are of same type and next to each other
//UNUSED
void merge_nodes(t_lexer **lexer)
{
    t_lexer *lex;
    t_lexer *node_to_remove;
    char    *merged_word;

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

// replace the value of expand nodes to the matching environment value
void	ft_expander(t_lexer **lexer, t_env *envb)
{
	// ft_printf("BEFORE EXPANDER =\n");
	// print_lexer(lexer);

	t_lexer	*lst;
	char	*tmp;

	lst = *lexer;
	while (lst)
	{
		if (lst->type == DQUOTE || lst->type == DMERGE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_dquote(tmp, lst, envb);
			// ft_printf("BEFORE CLEAN QUOTE FOR DQUOTES = [%s]\n", lst->word);
			lst = clean_quotes(lst);
			// ft_printf("AFTER CLEAN QUOTE FOR DQUOTES = [%s]\n", lst->word);
			
		}
		else if (lst->type == EXPAND || lst->type == EMERGE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_node2(tmp, lst, envb);
		}
		lst = lst->next;
	}
	// ft_printf("AFTER EXPANDER =\n");
	// print_lexer(lexer);
	clean_squotes(lexer);
	// ft_printf("AFTER CLEAN_SQUOTES =\n");
	// print_lexer(lexer);
	merge_nodes(lexer);
	// ft_printf("AFTER MERGE_NODES =\n");
	// print_lexer(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/22 09:20:35 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//merge two nodes when they are of same type and next to each other
//UNUSED
void	merge_lex_nodes(t_lexer **lexer, t_tokens type)
{
	t_lexer	*lex;
	char	*tmp;
	
	if (!lexer)
		return ;
	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == type && lex->next->type == type)
		{
			tmp = ft_strjoin(lex->word, lex->next->word);
			free(lex->word);
			lex->word = ft_strdup(tmp);
			ft_remove_lex_node(lexer, lex->next);
			free(tmp);
			// Continue from the current node as the next node is now different
		}
		else
		{
			// Progress to the next node only if no merge happened
			lex = lex->next;
		}
	}
}

void	merge_nodes(t_lexer **lexer)
{
	t_lexer	*lex;
	char	*tmp;
	char	*tmp2;

	lex = *lexer;
	while (lex && lex->next)
	{
		int	i;

		i = 0;
		while (lex->type >= 14)
		{
			if (i == 0)
			{
				tmp = ft_strdup(lex->word);
				lex = ft_remove_lex_node(lexer, lex);
				// lex = lex->next; // since ft_remove_lex_node return the previous node
				tmp2 = ft_strdup(lex->word);
				free (lex->word);
				lex->word = ft_strjoin(tmp, tmp2);
				ft_printf("lexjoin = [%s]__%s\n", lex->word, print_token(lex->type));
			}
			else
			{
				lex = lex->next;
				tmp = ft_strdup(lex->word);
				lex = ft_remove_lex_node(lexer, lex);
				lex = lex->next; // since ft_remove_lex_node return the previous node
				tmp2 = ft_strdup(lex->word);
				free (lex->word);
				lex->word = ft_strjoin(tmp, tmp2);
				i++;
			}
			free (tmp);
			free (tmp2);
		}
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
			lst = clean_quotes(lst);
		}
		else if (lst->type == EXPAND || lst->type == EMERGE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_node2(tmp, lst, envb);
		}
		lst = lst->next;
	}
	clean_squotes(lexer);
	ft_printf("BEFORE MERGE =\n");
	print_lexer(lexer);
	merge_nodes(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
}

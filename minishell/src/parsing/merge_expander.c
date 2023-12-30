/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:58:34 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 17:58:58 by esilbor          ###   ########.fr       */
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
		if (((lex->type >= SMERGE && lex->type <= EMERGE)
				|| lex->type == ISSPACE) && ((!(lex->next->type >= INPUT
						&& lex->next->type <= LIMITER)
					&& lex->next->type <= ISSPACE) || lex->next->type == PIPE))
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

void	ft_expander(t_lexer **lexer, t_env *envb)
{
	t_lexer	*lst;

	lst = *lexer;
	while (lst)
	{
		if (process_expander_node(&lst, envb) < 0)
		{
			free_lexer_list(lexer);
			return ;
		}
		lst = lst->next;
	}
}

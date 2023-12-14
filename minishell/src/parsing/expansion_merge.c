/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/14 07:36:46 by esilbor          ###   ########.fr       */
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
			&& !((lex->next->type >= 9 && lex->next->type <= 12)
				|| lex->next->type == PIPE))
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
		process_expander_node(&lst, envb);
		lst = lst->next;
	}
}

void	process_expander_node(t_lexer **lst, t_env *envb)
{
	char	*tmp;
	char	*esc;

	if ((*lst)->type == DQUOTE || (*lst)->type == DMERGE)
	{
		tmp = dol_to_expand((*lst)->word);
		if (tmp)
			*lst = expand_dquote(tmp, *lst, envb);
		esc = ft_strchr((*lst)->word, '\\');
		while (esc && esc[1] != '\"' && esc[1] != '?')
			clean_esc(lst, &esc);
		*lst = clean_quotes(*lst);
	}
	else if ((*lst)->type == EXPAND || (*lst)->type == EMERGE)
	{
		tmp = dol_to_expand((*lst)->word);
		if (tmp)
			*lst = expand_node2(tmp, *lst, envb);
		esc = ft_strchr((*lst)->word, '\\');
		while (esc && esc[1])
			clean_esc(lst, &esc);
	}
}

void	lexer_polish(t_lexer **lexer)
{
	clean_squotes(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
	clean_lexer2(lexer);
	clean_lexer3(lexer);
	merge_nodes(lexer);
	clean_lexer4(lexer);
	clean_empty_nodes(lexer);
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

// replace the value of expand nodes to the matching environment value
// void	ft_expander(t_lexer **lexer, t_env *envb)
// {
// 	t_lexer	*lst;
// 	char	*tmp;
// 	char	*esc;

// 	lst = *lexer;
// 	while (lst)
// 	{
// 		if (lst->type == DQUOTE || lst->type == DMERGE)
// 		{
// 			tmp = dol_to_expand(lst->word);
// 			if (tmp)
// 				lst = expand_dquote(tmp, lst, envb);
// 			esc = ft_strchr(lst->word, '\\');
// 			while (esc && esc[1] != '\"' && esc[1] != '?')
// 				clean_esc(&lst, &esc);
// 			lst = clean_quotes(lst);
// 		}
// 		else if (lst->type == EXPAND || lst->type == EMERGE)
// 		{
// 			tmp = dol_to_expand(lst->word);
// 			if (tmp)
// 				lst = expand_node2(tmp, lst, envb);
// 			esc = ft_strchr(lst->word, '\\');
// 			while (esc && esc[1])
// 				clean_esc(&lst, &esc);
// 		}
// 		lst = lst->next;
// 	}
// }
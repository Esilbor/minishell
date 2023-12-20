/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/20 08:41:41 by esilbor          ###   ########.fr       */
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
			&& !((lex->next->type >= INPUT && lex->next->type <= LIMITER)
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

t_lexer	**expand_cmds(t_lexer **lexer)
{
	t_lexer	*lex;
	char	**tab;
	int		i;

	lex = *lexer;
	i = 0;
	while (lex)
	{
		if (lex->type == EXPAND && ft_strchr(lex->word, ' ')) // should include tab as wspace?
		{
			tab = ft_split(lex->word, ' ');
			if (!tab)
				return (NULL);
			ft_remove_lex_node(lexer, lex);
			while (tab[i])
			{
				ft_add_lex_node(lexer, tab[i], WORD);
				i++;
			}
			ft_free_tab((void **) tab);
			break ;
		}
		lex = lex->next;
	}
	return (lexer);

}


void	lexer_polish(t_lexer **lexer)
{
	clean_squotes(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
	print_lexer(lexer, "after clean_lexer");
	clean_lexer2(lexer);
	print_lexer(lexer, "after clean_lexer2");
	clean_lexer3(lexer);
	print_lexer(lexer, "after clean_lexer3");
	merge_nodes(lexer);
	print_lexer(lexer, "after merge_nodes");


	lexer = expand_cmds(lexer);
	print_lexer(lexer, "after expand_cmds");


	clean_lexer4(lexer);
	print_lexer(lexer, "after clean_lexer4");
	clean_empty_nodes(lexer, WORD);
	print_lexer(lexer, "after clean_empty_nodes");
}

t_lexer	*parsing(char *input, t_lexer **lexer, t_env *envb)
{
	*lexer = ft_lexer(input);
	if (!(*lexer))
		return (add_history(input), NULL);
	add_history(input);
	print_lexer(lexer, "after ft_lexer");
	ft_expander(lexer, envb);
	clean_empty_nodes(lexer, EXPAND);
	print_lexer(lexer, "after ft_expander");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 18:45:21 by zaquedev         ###   ########.fr       */
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

int	process_expander_node(t_lexer **lst, t_env *envb)
{
	char	*tmp;
	char	*esc;

	if ((*lst)->type == DQUOTE || (*lst)->type == DMERGE)
	{
		tmp = dol_to_expand((*lst)->word);
		if (tmp)
		{
			*lst = expand_dquote(tmp, *lst, envb);
			if (!(*lst))
				return (-1);
		}
		esc = ft_strchr((*lst)->word, '\\');
		while (esc && esc[1] != '\"' && esc[1] != '?')
			if (clean_esc(lst, &esc) < 0)
				return (-1);
		*lst = clean_quotes(*lst);
	}
	else if ((*lst)->type == EXPAND || (*lst)->type == EMERGE)
	{
		tmp = dol_to_expand((*lst)->word);
		if (tmp)
		{
			*lst = expand_node2(tmp, *lst, envb);
			if (!(*lst))
				return (-1);
		}
		esc = ft_strchr((*lst)->word, '\\');
		while (esc && esc[1])
			if (clean_esc(lst, &esc) < 0)
				return (-1);
	}
	return (0);
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
		if (lex->type == EXPAND && lex->word[0] && lex->word[1]
			&& ft_strchr(&lex->word[1], ' '))
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

void	remove_space_nodes(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == ISSPACE && lex->word[0])
		{
			lex->type = WORD;
		}
		if (lex->type == ISSPACE || lex->type == QSPACE)
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
}

void	clean_space_nodes2(t_lexer **lexer)
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
			{
				free(tmp);
				free_lexer_list(lexer);
				return ;
			}
			free(previous->word);
			previous->word = ft_strjoin(tmp, " ");
			free (tmp);
			lex = lex->next;
		}
		previous = lex;
		lex = lex->next;
		i++;
	}
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

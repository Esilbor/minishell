/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:54 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/31 15:10:08 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_dquote_expand(t_lexer **lst, t_env *envb)
{
	char	*tmp;
	char	*esc;

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
	return (0);
}

static int	handle_expand(t_lexer **lst, t_env *envb)
{
	char	*tmp;
	char	*esc;

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
	return (0);
}

int	process_expander_node(t_lexer **lst, t_env *envb)
{
	if ((*lst)->type == DQUOTE || (*lst)->type == DMERGE)
	{
		if (handle_dquote_expand(lst, envb) < 0)
			return (-1);
	}
	else if ((*lst)->type == EXPAND || (*lst)->type == EMERGE)
	{
		if (handle_expand(lst, envb) < 0)
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
				ft_add_lex_node(lexer, tab[i++], WORD);
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

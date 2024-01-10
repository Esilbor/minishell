/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:03:11 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/10 13:13:52 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Remove a specified node from lexer linked list
t_lexer	*ft_remove_lex_node(t_lexer **lexer, t_lexer *node_to_remove)
{
	t_lexer	*current;
	t_lexer	*prev;

	current = *lexer;
	prev = NULL;
	if (current != NULL && current == node_to_remove)
	{
		*lexer = current->next;
		free(node_to_remove->word);
		free(node_to_remove);
		return (*lexer);
	}
	while (current != NULL && current != node_to_remove)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return (node_to_remove);
	prev->next = current->next;
	free(current->word);
	free(current);
	return (prev);
}

static t_lexer	*semi_column_case(char *var, t_lexer *node)
{
	char	*tmp_str;

	tmp_str = ft_strjoin("$", var);
	if (!tmp_str && var)
		return (free(var), NULL);
	free (node->word);
	node->word = ft_strdup(tmp_str);
	if (!node->word && tmp_str)
		return (free(var), free(tmp_str), NULL);
	free (tmp_str);
	free (var);
	return (node);
}

static void	expand_begining(char *var, char **new_str, char **tmp_str)
{
	if (var)
	{
		*new_str = ft_strjoin(*tmp_str, var);
		if (!(*new_str) && *tmp_str)
		{
			free(*tmp_str);
			free(var);
			return ;
		}
	}
	else
	{
		*new_str = ft_strdup(*tmp_str);
		if (!(*new_str) && *tmp_str)
		{
			free (*tmp_str);
			return ;
		}
	}
	free (var);
	free (*tmp_str);
}

// Recursively expand lexer node for env variables (not within quotes)
t_lexer	*expand_node2(char *tmp, t_lexer *node, t_env *envb)
{
	char	*var;
	char	*new_str;
	char	*tmp_str;
	char	*ptr;

	var = extract_var(tmp + 1, &ptr);
	if (var && (var[0] == '=' || var[0] == ':'))
		return (semi_column_case(var, node));
	else
		tmp_str = ft_strpcpy(node->word, tmp);
	get_env_value(envb, &var);
	expand_begining(var, &new_str, &tmp_str);
	if (ptr)
		tmp_str = ft_strjoin(new_str, ptr);
	free (node->word);
	free (new_str);
	node->word = ft_strdup(tmp_str);
	if (!node->word && tmp_str)
		return (free (tmp_str), NULL);
	free (tmp_str);
	tmp = dol_to_expand(node->word);
	if (tmp)
		node = expand_node2(tmp, node, envb);
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/28 12:04:53 by esilbor          ###   ########.fr       */
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

// Expand lexer node for environment variable
t_lexer	*expand_node(t_lexer **lexer, t_lexer *lst, t_env *envb)
{
	char	*tmp;
	t_env	*var;

	var = get_env_node(envb, lst->word);
	if (var)
	{
		tmp = ft_strchr(var->var_str, '=');
		if (tmp)
		{
			tmp++;
			free(lst->word);
			lst->word = ft_strdup(tmp);
			lst->type = WORD;
		}
	}
	else
		lst = ft_remove_lex_node(lexer, lst);
	return (lst);
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
	{
		tmp_str = ft_strjoin("$", var);
		free (node->word);
		node->word = ft_strdup(tmp_str);
		free (tmp_str);
		free (var);
		return (node);
	}
	else
		tmp_str = ft_strpcpy(node->word, tmp);
	get_env_value(envb, &var);
	if (var)
		new_str = ft_strjoin(tmp_str, var);
	else
		new_str = ft_strdup(tmp_str);
	free (var);
	free (tmp_str);
	if (ptr)
	{
		tmp_str = ft_strjoin(new_str, ptr);
	}
	free (node->word);
	free (new_str);
	node->word = ft_strdup(tmp_str);
	free (tmp_str);
	tmp = dol_to_expand(node->word);
	if (tmp)
		node = expand_node2(tmp, node, envb);
	return (node);
}

//Extracts substring from `str` until space, $, or ", sets `ptr` to remainder.
char	*extract_var(char *str, char **ptr)
{
	char		*var;
	size_t		i;

	i = 0;
	var = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[0] == '?'
			|| str[0] == '=' || str[0] == ':' || str[0] == '!' || str[0] == '*'
			|| str[0] == '@'))
	{
		if (str[0] == '?' || str[0] == '!' || str[0] == '*' || str[0] == '@'
			|| ft_isdigit(str[0]))
		{
			*ptr = &str[1];
			var = malloc(sizeof(char) * i + 1);
			if (!var)
				return (NULL);
			if (str[0] == '!' || str[0] == '*' || str[0] == '@'
				|| ft_isdigit(str[0]))
				ft_strlcpy(var, str, i + 1);
			else
				ft_strlcpy(var, str, i + 2);
			return (var);
		}
		i++;
	}
	*ptr = &str[i];
	var = malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	ft_strlcpy(var, str, i + 1);
	return (var);
}

//Searches `envb` for `*str`, return env value,
//or NULL if not found.
char	*get_env_value(t_env *envb, char **str)
{
	size_t	str_len;

	str_len = ft_strlen(*str);
	while (envb)
	{
		if (!ft_strncmp(envb->var_str, *str, str_len)
			&& envb->var_str[str_len] == '=')
		{
			free (*str);
			*str = ft_strdup(&envb->var_str[str_len + 1]);
			if (!(*str))
				return (NULL);
			return (*str);
		}
		else
		{
			envb = envb->next;
		}
	}
	free (*str);
	*str = NULL;
	return (*str);
}

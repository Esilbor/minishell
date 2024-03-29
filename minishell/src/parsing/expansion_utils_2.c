/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/10 13:06:33 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//return a pointer to a dollar to expand or NULL if none
char	*dol_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && (str[i + 1]) != ' '
			&& str[i + 1] != '"' && str[i + 1] != '=')
		{
			if (i > 0 && str[i - 1] == '\\')
				i ++;
			else
				return (&str[i]);
		}
		else
			i ++;
	}
	return (NULL);
}

static int	allocate_new_str(char *tmp_str, char *var, char **new_str)
{
	if (var)
	{
		*new_str = ft_strjoin(tmp_str, var);
		if (!(*new_str) && tmp_str)
			return (free (tmp_str), -1);
	}
	else
	{
		*new_str = ft_strdup(tmp_str);
		if (!(*new_str) && tmp_str)
			return (free (tmp_str), -1);
	}
	free (var);
	free (tmp_str);
	return (0);
}

// Recursively expand lexer node for env variables (within double quotes)
t_lexer	*expand_dquote(char *tmp, t_lexer *node, t_env *envb)
{
	char	*var;
	char	*new_str;
	char	*tmp_str;
	char	*ptr;

	var = extract_var(tmp + 1, &ptr);
	tmp_str = ft_strpcpy(node->word, tmp);
	get_env_value(envb, &var);
	if (allocate_new_str(tmp_str, var, &new_str) < 0)
		return (NULL);
	if (ptr)
		tmp_str = ft_strjoin(new_str, ptr);
	free (new_str);
	free (node->word);
	node->word = ft_strdup(tmp_str);
	if (!node->word && tmp_str)
		return (free (tmp_str), NULL);
	free (tmp_str);
	tmp = dol_to_expand(node->word);
	if (tmp)
		node = expand_dquote(tmp, node, envb);
	return (node);
}

// Remove quotes from lexer node and update type to WORD
t_lexer	*clean_quotes(t_lexer *node)
{
	char	*new_str;

	new_str = ft_strndup(&node->word[1], ft_strlen2(node->word) - 2);
	free (node->word);
	node->word = new_str;
	if (!new_str[0])
	{
		node->type = ISSPACE;
	}
	return (node);
}

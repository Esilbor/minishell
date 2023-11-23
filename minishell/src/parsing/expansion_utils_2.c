/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/23 09:52:23 by esilbor          ###   ########.fr       */
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
		if (str[i] == '$' && (str[i + 1]) != ' ' && str[i + 1] != '"' && str[i + 1] != '\'')
		{
			if (i > 0)
			{
				if (str[i - 1] == '\\') // work to be done here
					return (NULL);
			}			
			return (&str[i]);
		}
		i ++;
	}
	return (NULL);
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
	get_env_value(envb, &var); //updates USER into bbresil
	if (var)
		new_str = ft_strjoin(tmp_str, var); //join "this is \0 with bbresil
	else
		new_str = ft_strdup(tmp_str);
	free (var); // if var is NULL nothing will occur :)
	free (tmp_str);
	if (ptr)
		tmp_str = ft_strjoin(new_str, ptr);// "this is bbresil"
	free (node->word);
	free (new_str);
	node->word = ft_strdup(tmp_str);
	free (tmp_str);
	tmp = dol_to_expand(node->word);
	if (tmp)
		node = expand_dquote(tmp, node, envb); // RECURSIVITÉ
	return (node);
}

// Remove quotes from lexer node and update type to WORD
t_lexer	*clean_quotes(t_lexer *node)
{
	char	*new_str;

	new_str = ft_strndup(&node->word[1], ft_strlen2(node->word) - 2);
	free (node->word);
	node->word = new_str;
	// free (new_str);
	return (node);
}

// Candy_$hell> echo "this $$$$$$$$$$$?"
// [echo__WORD__][this 0__DQUOTE__]
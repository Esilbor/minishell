/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/12 19:41:22 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*ft_remove_lex_node(t_lexer **lexer, t_lexer *node_to_remove)
{
	t_lexer	*current;
	t_lexer	*prev;

	current = *lexer;
	prev = NULL;
	if (current != NULL && current == node_to_remove) // Handle the case where the node to remove is the head of the list
	{
		*lexer = current->next; // Change head
		free(node_to_remove->word); // Free the memory of the word
		free(node_to_remove); // Free the memory of the node
		return (*lexer);
	}
	while (current != NULL && current != node_to_remove) // Find the node before the node to remove
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL) // If the node was not found, return
		return (node_to_remove);
	prev->next = current->next; // Unlink the node from the linked list
	free(current->word); // Free the memory of the word
	free(current); // Free the memory of the node
	return (prev);
}

t_lexer	*expand_node(t_lexer **lexer, t_lexer *lst, t_env *envb)
{
	char	*tmp;
	t_env	*var;

	var = get_env_node(envb, lst->word);
	if (var)
	{
		tmp = ft_strchr(var->var_str, '=');
		if (tmp) // i dont think it is necessary
		{
			tmp++;
			free(lst->word);
			lst->word = ft_strdup(tmp); // to protect
			lst->type = WORD;
		}
	}
	else
		lst = ft_remove_lex_node(lexer, lst);// REMOVE NODE FROM LEXER AND CONTINUE
	return (lst);
}

//Extracts substring from `str` until space, $, or ", sets `ptr` to remainder.
char	*extract_var(char *str, char **ptr)
{
	char		*var;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	var = NULL;
	// while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\"'  && str[i] != '\'')
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	*ptr = &str[i];
	var = malloc(sizeof(char) * i + 1);
	ft_strlcpy(var, str, i + 1);
	return (var);
}

//Searches `envb` for `*str`, replaces `*str` with env value,
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

//return a pointer to a dollar to expand or NULL if none
char	*dol_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && (str[i + 1]) != ' ' && str[i + 1] != '"' && str[i + 1] != '\'')
			return (&str[i]);
		i ++;
	}
	return (NULL);
}

t_lexer	*expand_dquote(char *tmp, t_lexer *node, t_env *envb)
{
	char	*var;
	char	*new_str;
	char	*tmp_str;
	char	*ptr;

	var = extract_var(tmp + 1, &ptr); //get USER and set ptr to the remainder so "
	tmp_str = ft_strpcpy(node->word, tmp);//copies everthing before $ "this is \0
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

t_lexer	*clean_dquotes(t_lexer *node)
{
	char	*new_str;

	new_str = ft_strndup(&node->word[1], ft_strlen2(node->word) - 2);
	free (node->word);
	node->word = new_str;
	node->type = WORD; // might be too soon??
	return (node);
}

// replace the value of expand nodes to the matching environment value
void	ft_expander(t_lexer **lexer, t_env *envb)
{
	t_lexer	*lst;
	char	*tmp;

	lst = *lexer;
	while (lst)
	{
		if (lst->type == EXPAND)
			lst = expand_node(lexer, lst, envb);
		else if (lst->type == DQUOTE)
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_dquote(tmp, lst, envb);
			lst = clean_dquotes(lst); // remove initial and final "
		}
		lst = lst->next;
	}
}

// Candy_$hell> echo "this $$$$$$$$$$$?"
// [echo__WORD__][this 0__DQUOTE__]

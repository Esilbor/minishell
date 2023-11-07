/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/07 20:33:40 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_lexer *ft_remove_lex_node(t_lexer **lexer, t_lexer *node_to_remove)
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

char	*extract_var(char *tmp)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = NULL;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '$')
		i++;
	var = malloc(sizeof(char) * i);
	while (j < i)
	{
		var[j] = tmp[j];
		i++;
	}
	var[i] = '\0';
	printf("var= %s\n", var);
	return (var);
}

void	expand_dquote(/* t_lexer **lexer, */ t_lexer *lst /* , t_env *envb */)
{
	char	*tmp;
	char	*var;
	tmp = ft_strchr(lst->word, '$');
	if (tmp && (tmp + 1) && *(tmp + 1) != ' ')
	{
		printf
		var = extract_var(tmp + 1);
	}
}

// replace the value of expand nodes to the matching environment value
void	ft_expander(t_lexer **lexer, t_env *envb)
{
	t_lexer	*lst;
	// t_env	*var;
	// char	*tmp;

	lst = *lexer;
	// var = NULL;
	while (lst)
	{
		if (lst->type == EXPAND)
			lst = expand_node(lexer, lst, envb);
		else if (lst->type == DQUOTE)
		{
			/* lst = */expand_dquote(/* lexer,  */lst/* , envb */);
		}
		lst = lst->next;
	}
}

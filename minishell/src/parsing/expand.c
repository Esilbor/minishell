/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/20 23:16:52 by esilbor          ###   ########.fr       */
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

// Expand lexer node for environment variable
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

	i = 0;
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

// Recursively expand lexer node for env variables (not within quotes)
t_lexer	*expand_node2(char *tmp, t_lexer *node, t_env *envb)
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
		node = expand_node2(tmp, node, envb); // RECURSIVITÉ
	return (node);
}

// Recursively expand lexer node for env variables (within double quotes)
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

// Remove quotes from lexer node and update type to WORD
t_lexer	*clean_quotes(t_lexer *node)
{
	char	*new_str;

	new_str = ft_strndup(&node->word[1], ft_strlen2(node->word) - 2);
	free (node->word);
	node->word = new_str;
	// node->type = WORD; // might be too soon?? yes it was too soon for XMERGE types
	return (node);
}

//Processes lexer tokens, removing << < > and >> types from the list.
void	clean_lexer3(t_lexer **lexer)
{
	t_lexer *lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == LESS_LESS || lex->type == LESS
			|| lex->type == GREAT || lex->type == GREAT_GREAT)
		{
			lex = ft_remove_lex_node(lexer, lex);
		}
		if (lex->type == EXPAND && lex->word[0] == '\0') // IMPORTANT NOTE all pointers are initiated therefore never NULL must use [0]
			lex = ft_remove_lex_node(lexer, lex);
		if (lex->type == WORD && lex->word[0] == '\0')
			lex = ft_remove_lex_node(lexer, lex);
		lex = lex->next;
	}
}

// clean and attribute nodes of type LIMITER, APPEND, INPUT or OUTPUT
void	clean_redir(t_lexer **lexer, t_lexer **lex, t_tokens type)
{
	t_tokens	token;
	
	token = type - 7;
	if (token <= 1)
	{
		ft_putstr_fd("invalid clean_redir type\n", 2);
		return ;
	}
	*lex = (*lex)->next;
	if (!(*lex)->word[0])
	{
		*lex = ft_remove_lex_node(lexer, *lex);
		*lex = (*lex)->next;		
	}
	if (*lex)
		(*lex)->type = type;
	
}

//Processes lexer tokens, setting limiter and append types.
void	clean_lexer2(t_lexer **lexer)
{
	t_lexer *lex;

	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS_LESS
			&& (lex->next->type == WORD || lex->next->type == EXPAND))
			clean_redir(lexer, &lex, LIMITER);
		else if (lex->type == GREAT_GREAT && (lex->next->type == WORD || lex->next->type == EXPAND))
			clean_redir(lexer, &lex, APPEND);
		if (lex)
			lex = lex->next;
	}
	clean_lexer3(lexer);
}

void	clean_squotes(t_lexer **lexer)
{
	t_lexer *lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == SQUOTE || lex->type == SMERGE)
			lex = clean_quotes(lex);
		lex = lex->next;
	}
}

//Processes lexer tokens, cleaning quotes and setting input/output types.
void	clean_lexer(t_lexer **lexer)
{
	t_lexer *lex;

	lex = *lexer;
	// while (lex)
	// {
	// 	if (lex->type == SQUOTE || lex->type == SMERGE)
	// 		lex = clean_quotes(lex);
	// 	lex = lex->next;
	// }
	// lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == LESS && (lex->next->type == WORD || lex->next->type == EXPAND))
			clean_redir(lexer, &lex, INPUT);
		else if (lex->type == GREAT && (lex->next->type == WORD || lex->next->type == EXPAND))
			clean_redir(lexer, &lex, OUTPUT);
		if (lex)
			lex = lex->next;
	}
	clean_lexer2(lexer);
}

//merge two nodes when they are of same type and next to each other
void	merge_lex_nodes(t_lexer **lexer, t_tokens type)
{
	t_lexer	*lex;
	char	*tmp;
	
	if (!lexer)
		return ;
	lex = *lexer;
	while (lex && lex->next)
	{
		if (lex->type == type && lex->next->type == type)
		{
			tmp = ft_strjoin(lex->word, lex->next->word);
			free(lex->word);
			lex->word = ft_strdup(tmp);
			ft_remove_lex_node(lexer, lex->next);
			free(tmp);
			// Continue from the current node as the next node is now different
		}
		else
		{
			// Progress to the next node only if no merge happened
			lex = lex->next;
		}
	}
}

void	merge_nodes(t_lexer **lexer)
{
	t_lexer	*lex;
	char	*tmp;
	char	*tmp2;

	lex = *lexer;
	while (lex && lex->next)
	{
		while (lex->type >= 14)
		{
			tmp = ft_strdup(lex->word);
			lex = ft_remove_lex_node(lexer, lex);
			lex = lex->next; // since ft_remove_lex_node return the previous node
			tmp2 = ft_strdup(lex->word);
			free (lex->word);
			lex->word = ft_strjoin(tmp, tmp2);
			free (tmp);
		}
		lex = lex->next;
	}
	
}
//finally change SQUOTES and DQUOTES into WORDS before cleaning
void	quotes_to_words(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->type == SQUOTE || lex->type == DQUOTE)
			lex->type = WORD;
		lex = lex->next;
	}
}

// replace the value of expand nodes to the matching environment value
void	ft_expander(t_lexer **lexer, t_env *envb)
{
	t_lexer	*lst;
	char	*tmp;

	lst = *lexer;
	while (lst)
	{
		if (lst->type == DQUOTE || lst->type == DMERGE) // make a duplicate for EXPAND type************************
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_dquote(tmp, lst, envb);
			lst = clean_quotes(lst); // remove initial and final "
		}
		else if (lst->type == EXPAND || lst->type == EMERGE) // make a duplicate for EXPAND type need EMERGE type
		{
			tmp = dol_to_expand(lst->word);
			if (tmp)
				lst = expand_node2(tmp, lst, envb);
		}
		lst = lst->next;
	}
	ft_printf("before clean= ");
	print_lexer(lexer);
	// CLEAN QUOTES 
	clean_squotes(lexer);
	ft_printf("after clean_squotes= ");
	print_lexer(lexer);
	merge_nodes(lexer);
	ft_printf("AFTER MERGE_NODES= ");
	print_lexer(lexer);
	quotes_to_words(lexer);
	clean_lexer(lexer);
	ft_printf("after clean_lexer= ");
	print_lexer(lexer);
}

// Candy_$hell> echo "this $$$$$$$$$$$?"
// [echo__WORD__][this 0__DQUOTE__]

/*
Candy_$hell> $YUY


CMD[0] = [__EXPAND]

********index = 0 ********


CMD[0]
cmd[0] =

***************
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:12:40 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/30 15:23:12 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// return the last node of the lexer
t_lexer	*ft_last_lexer_node(t_lexer *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

void	ft_add_lex_node(t_lexer **lexer, char *word, t_tokens type)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	new_node->word = ft_strdup(word);
	new_node->type = type;
	new_node->next = NULL;
	if (*lexer == NULL)
		*lexer = new_node;
	else
		ft_last_lexer_node(*lexer)->next = new_node;
}

t_lexer	*syntax_error(t_lexer *lexer, t_lexer **lexer_head)
{
	ft_putstr_fd("syntax error near unexpected A token '", 2);
	ft_putstr_fd(lexer->word, 2);
	ft_putstr_fd("'\n", 2);
	free_lexer_list(lexer_head);
	return (NULL);
}

// Check validity of lexer tokens in the input
t_lexer	*check_valid_input(t_lexer **lexer_head)
{
	ft_printf("entering check valid\n");
	t_lexer	*x;
	int		i;

	x = *lexer_head;
	i = 0;
	if (!x)
		return (NULL);
	while (x)
	{
		if (x->type == PIPE && !i)
		{
			
			ft_printf("this is A\n");	
			return (syntax_error(x, lexer_head));
		}
		if (x->type >= PIPE && x->type <= 5 && x->next)
		{
			if ((x->next->type >= 1 && x->next->type < 5))
			{
				ft_printf("this is B\n");	
				return (syntax_error(x, lexer_head));
			}
		}
		else if (x->type == LESS_LESS && (!x->next || x->next->type != WORD))
		{
			ft_printf("this is C\n");	
			return (syntax_error(x, lexer_head));
		}
		if (!x->next && x->type && x->type <= 5/*  && x->type > 0 */)
		{
			ft_printf("this is D\n");	
			return (syntax_error(x, lexer_head));
		}
		i++;
		x = x->next;
	}
	return (*lexer_head);
}

//clean the lexer of null nodes of type WORD
t_lexer	**clean_empty_nodes(t_lexer **lexer)
{
	print_lexer(lexer, "before clean_empty_node");
	t_lexer	*lex;
	
	lex = *lexer;
	while (lex)
	{
		if (lex->type == WORD && lex->word[0] == '\0')
		{
			lex = ft_remove_lex_node(lexer, lex);
			ft_printf("YOUHOOO\n");
		}
		lex = lex->next;
	}
	// lex = *lexer;
	return (lexer);
}

// Perform lexical analysis on the input line
t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lexer_list;
	char	*epur_line;

	lexer_list = NULL;
	epur_line = ft_epur_str(line);
	if (!epur_line)
		return (NULL);
	ft_printf(CYAN"epur_line = [%s]\n"RESET, epur_line);
	if (ft_fill_lexer(&lexer_list, epur_line))
	{
		free (epur_line);
		free_lexer_list(&lexer_list);
		return (NULL);
	}
	free(epur_line);
	if (lexer_list->word[0] == '\0')
		lexer_list = ft_remove_lex_node(&lexer_list, lexer_list);
	clean_empty_nodes(&lexer_list);
	print_lexer(&lexer_list, "ft_lexer");
	return (check_valid_input(&lexer_list));
}

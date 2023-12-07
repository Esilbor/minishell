/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:14:20 by bbresil           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/28 14:53:24 by zaquedev         ###   ########.fr       */
=======
/*   Updated: 2023/11/30 15:08:11 by esilbor          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer_list(t_lexer **head)
{
	t_lexer	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->word);
		free(tmp);
	}
}

// return 1 if c is a space or a tab else 0
int	is_wspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// return 1 if char c is a single or double quote
int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_epur_str(char *str)
{
	int		i;
	int		j;
	char	*epur_str;

	i = 0;
	j = 0;
	epur_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!str || !epur_str)
		return (NULL);
	while (str[i]/*  && str[i + 1] */)
	{
		while (is_wspace(str[i]) && is_wspace(str[i + 1]))
			i++;
		if (is_wspace(str[i]))
			i++;
		if (is_quote(str[i]))
			handle_quote(str, &i, &j, epur_str);
		else
			handle_non_quote(str, &i, &j, epur_str);
	}
	epur_str[j] = '\0';
	if (epur_str[0])
		return (epur_str);
	free (epur_str);
	return (NULL);
}

// Fill lexer list from cmd_line string
int	ft_fill_lexer(t_lexer **lexer_lst, char *cmd_line)
{
	int		i;
	t_lexer	*head;

	i = 0;
	head = *lexer_lst;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\"')
		{
			if (handle_dquotes(cmd_line, &i, &head))
				return (*lexer_lst = head, 1);
		}
		else if (cmd_line[i] == '\'')
		{
			if (handle_squotes(cmd_line, &i, &head))
				return (*lexer_lst = head, 1);
		}
		else
			handle_words_spec_char(cmd_line, &i, &head);
		while (cmd_line[i] && cmd_line[i] == ' ')
			i++;
	}
	*lexer_lst = head;
	// print_lexer(lexer_lst, "after ft_fill_lexer");
	return (0);
}

/*******************************************************************/
/******************PRINT FUNCTIONS TO BE DELETED********************/
/*******************************************************************/
/*******************************************************************/

char	*print_token(t_tokens token)
{
	if (token == WORD)
		return ("WORD");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == LESS)
		return ("LESS");
	else if (token == GREAT)
		return ("GREAT");
	else if (token == LESS_LESS)
		return ("LESS_LESS");
	else if (token == GREAT_GREAT)
		return ("GREAT_GREAT");
	else if (token == DOLLAR)
		return ("DOLLAR");
	else if (token == DQUOTE)
		return ("DQUOTE");
	else if (token == SQUOTE)
		return ("SQUOTE");
	else if (token == EXPAND)
		return ("EXPAND");
	else if (token == LIMITER)
		return ("LIMITER");
	else if (token == INPUT)
		return ("INPUT");
	else if (token == OUTPUT)
		return ("OUTPUT");
	else if (token == APPEND)
		return ("APPEND");
	else if (token == SMERGE)
		return ("SMERGE");
	else if (token == DMERGE)
		return ("DMERGE");
	else if (token == WMERGE)
		return ("WMERGE");
	else if (token == EMERGE)
		return ("EMERGE");
	return ("ERROR");
}

void	print_lexer(t_lexer **head, char *loc)
{
	t_lexer	*lst;
	int		i;

	lst = *head;
	i = 0;
	ft_printf(PINK"\n%s\n"RESET, loc);
	ft_printf(WHITE"CMD[%d] = ", i++);
	while (lst)
	{
		if (lst->type == WORD)
			ft_printf(GREEN"[%s__WORD__]"RESET, lst->word);
		else if (lst->type == PIPE)
		{
			ft_printf(PINK"[%s__PIPE__]"RESET, lst->word);
			ft_printf("\n\n");
			ft_printf(WHITE"CMD[%d] = ", i++);
		}
		else if (lst->type == LIMITER)
			ft_printf(BLUE"[%s__LIMITER__]"RESET, lst->word);
		else if (lst->type == INPUT)
			ft_printf(CYAN"[%s__INPUT__]"RESET, lst->word);
		else if (lst->type == OUTPUT)
			ft_printf(YELLOW"[%s__OUTPUT__]"RESET, lst->word);
		else if (lst->type == APPEND)
			ft_printf(YELLOW"[%s__APPEND__]"RESET, lst->word);
		else if (lst)
			ft_printf(RED"[%s__%s]"RESET, lst->word, print_token(lst->type));
		lst = lst->next;
	}
	ft_printf("\n");
}

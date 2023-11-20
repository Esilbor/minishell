/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:14:20 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/20 19:44:14 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_lexer_list(t_lexer **head)
{
	t_lexer *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->word);
		free(tmp);
	}
}

// return 1 if c is a space or a tab else 0
int is_wspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// return 1 if char c is a single or double quote
static int  is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	handle_non_quote(char *str, int *i, int *j, char *epur_str)
{
    while (str[*i] && !is_wspace(str[*i]) && !is_quote(str[*i]))
        epur_str[(*j)++] = str[(*i)++];
    while (is_wspace(str[*i]) && is_wspace(str[*i + 1]))
        (*i)++;
    if (str[*i] && str[*i + 1] && !is_quote(str[*i]) && is_wspace(str[*i]))
        epur_str[(*j)++] = str[(*i)++];
}


void	handle_quote(char *str, int *i, int *j, char *epur_str)
{
	char quote_char;
	
	quote_char = str[*i];
	epur_str[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != quote_char)
		epur_str[(*j)++] = str[(*i)++];
	if (str[*i] == quote_char)
		epur_str[(*j)++] = str[(*i)++];
}

char	*ft_epur_str(char *str)
{
	int	i;
	int	j;
	char *epur_str;
	
	i = 0;
	j = 0;
	epur_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!str || !epur_str)
		return (NULL);
	while (str[i]/*  && str[i + 1] */)
	{
		while (is_wspace(str[i]) && is_wspace(str[i + 1]) /* || !is_quote(str[i]) */)
			i++;
		if (is_quote(str[i]))
			handle_quote(str, &i, &j, epur_str);
		else
			handle_non_quote(str, &i, &j, epur_str);
	}
	epur_str[j] = '\0';
	return (epur_str);
}

// Detects shell symbols (|, <, >, >>, <<, quotes), defaults to WORD
t_tokens is_spec_char2(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (*c == '"')
		return (DQUOTE);
	else if (*c == '\'')
		return (SQUOTE);
	return (WORD);
}

// Detects shell symbols (|, <, >, $, >>, <<), defaults to WORD
t_tokens is_spec_char3(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '$')
		return (DOLLAR);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	return (WORD);
}

// Detects shell symbols (|, <, >, >>, <<, quotes, $), defaults to WORD
t_tokens is_spec_char(char *c)
{
	if (*c == '|')
		return (PIPE);
	else if (*c == '$')
		return (DOLLAR);
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (LESS_LESS);
		return (LESS);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (*c == '"')
		return (DQUOTE);
	else if (*c == '\'')
		return (SQUOTE);
	return (WORD);
}

// return the last node of the lexer
t_lexer *ft_last_lexer_node(t_lexer *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

void ft_add_lex_node(t_lexer **lexer, char *word, t_tokens type)
{
	t_lexer *new_node;

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

// Handles single quotes in 'cmd_line', adds to lexer list, checks for errors
int	handle_squotes(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (cmd_line[j] && cmd_line[j] != '\'')
		j++;
	if (!cmd_line[j])
	{
		ft_putstr_fd("Candy_$hell: syntax error: unclosed Squote\n", 2);
		*i = j;
		return (1);
	}
	else if (cmd_line[j + 1] && cmd_line[j + 1] != ' ' && !is_spec_char3(&cmd_line[j + 1]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
		ft_add_lex_node(head, tmp, SMERGE);
	}
	else
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
		ft_add_lex_node(head, tmp, SQUOTE);
	}
	free(tmp);
	*i = j + 1;
	return (0);
}

int	handle_dquotes(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (cmd_line[j] && cmd_line[j] != '\"')
		j++;
	if (!cmd_line[j])
	{
		ft_putstr_fd("Candy_$hell: syntax error: unclosed Dquote\n", 2);
		*i = j;
		return (1);
	}
	else if (cmd_line[j + 1] && cmd_line[j + 1] != ' ' && !is_spec_char3(&cmd_line[j + 1]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
		ft_add_lex_node(head, tmp, DMERGE);
	}
	else
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
		ft_add_lex_node(head, tmp, DQUOTE);
	}
	free(tmp);
	*i = j + 1;
	return (0);
}

// int	handle_dquotes(char *cmd_line, int *i, t_lexer **head)
// {
// 	int		j;
// 	char	*tmp;

// 	j = *i + 1;
// 	while (cmd_line[j] && cmd_line[j] != '\"')
// 		j++;
// 	if (!cmd_line[j])
// 	{
// 		ft_putstr_fd("Candy_$hell: syntax error: unclosed Dquote\n", 2);
// 		*i = j;
// 		return (1);
// 	}
// 	else
// 	{
// 		tmp = ft_strndup(&cmd_line[*i], j - *i + 1);
// 		ft_add_lex_node(head, tmp, DQUOTE);
// 		free(tmp);
// 		*i = j + 1;
// 	}
// 	return (0);
// }

// Processes double quotes in 'cmd_line', updates lexer, handles syntax errors
void	handle_spec_chars(char *cmd_line, int *j, t_lexer **head)
{
	char	*tmp;

	if ((is_spec_char(&cmd_line[*j]) == LESS_LESS ||
		is_spec_char(&cmd_line[*j]) == GREAT_GREAT) && cmd_line[*j + 1])
	{
		tmp = ft_strndup(&cmd_line[*j], 2);
		ft_add_lex_node(head, tmp, is_spec_char(&cmd_line[*j]));
		free(tmp);
		*j += 2;
	}
	else if (is_spec_char(&cmd_line[*j]) == DOLLAR && cmd_line[*j + 1]
		&& cmd_line[*j + 1] != ' ')
		handle_dollar(cmd_line, j, head);
	else
	{
		tmp = ft_strndup(&cmd_line[*j], 1);
		ft_add_lex_node(head, tmp, is_spec_char2(&cmd_line[*j])); /*2*/
		free(tmp);
		(*j)++;
	}
}

// Handle dollar signs and variable expansion
void	handle_dollar(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (cmd_line[j] && !is_spec_char2(&cmd_line[j]) && cmd_line[j] != ' ')
		j++;

	if (j > *i)
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, EXPAND);
		free(tmp);
	}
	*i = j;
}

// Process words with special chars in cmd_line
void	handle_words_spec_char(char *cmd_line, int *i, t_lexer **head)
{
	int		j;
	char	*tmp;

	j = *i;
	while (cmd_line[j] && !is_spec_char(&cmd_line[j]) && cmd_line[j] != ' ')
		j++;


	if (cmd_line[j] && cmd_line[j] != ' ' && !is_spec_char3(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WMERGE); /*****************************************************************/
		free(tmp);
	}
	else if (!cmd_line[j] || cmd_line[j] == ' ' || is_spec_char3(&cmd_line[j]))
	{
		tmp = ft_strndup(&cmd_line[*i], j - *i);
		ft_add_lex_node(head, tmp, WORD);
		free(tmp);
	}
	if (is_spec_char3(&cmd_line[j]))
		handle_spec_chars(cmd_line, &j, head);
	*i = j;
}

// void	handle_words_spec_char(char *cmd_line, int *i, t_lexer **head)
// {
// 	int		j;
// 	char	*tmp;

// 	j = *i;
// 	while (cmd_line[j] && !is_spec_char(&cmd_line[j]) && cmd_line[j] != ' ')
// 		j++;

// 	if (j > *i)
// 	{
// 		tmp = ft_strndup(&cmd_line[*i], j - *i);
// 		ft_add_lex_node(head, tmp, WORD); /*****************************************************************/
// 		free(tmp);
// 	}
// 	else
// 		handle_spec_chars(cmd_line, &j, head);
// 	*i = j;
// }

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
				return (1);
		}
		else if (cmd_line[i] == '\'')
		{
			if (handle_squotes(cmd_line, &i, &head))
				return (1);

		}
		else
		{
			handle_words_spec_char(cmd_line, &i, &head);
		}
		while (cmd_line[i] && cmd_line[i] == ' ')
			i++;
	}
	*lexer_lst = head;
	return (0);
}

char	*print_token(t_tokens token) // A SUPPRIMER
{
	if (token == WORD)
		return ("WORD");
	else if(token == PIPE)
		return ("PIPE");
	else if(token == LESS)
		return ("LESS");
	else if(token == GREAT)
		return ("GREAT");
	else if(token == LESS_LESS)
		return ("LESS_LESS");
	else if(token == GREAT_GREAT)
		return ("GREAT_GREAT");
	else if(token == DOLLAR)
		return ("DOLLAR");
	else if(token == DQUOTE)
		return ("DQUOTE");
	else if(token == SQUOTE)
		return ("SQUOTE");
	else if(token == EXPAND)
		return ("EXPAND");
	else if(token == LIMITER)
		return ("LIMITER");
	else if(token == INPUT)
		return ("INPUT");
	else if(token == OUTPUT)
		return ("OUTPUT");
	else if(token == APPEND)
		return ("APPEND");
	else if(token == SMERGE)
		return ("SMERGE");
	else if(token == DMERGE)
		return ("DMERGE");
	else if(token == WMERGE)
		return ("WMERGE");
	return ("ERROR");
}

void print_lexer(t_lexer **head)
{
	t_lexer *lst;
	int		i;

	lst = *head;
	i = 0;
	ft_printf("\n\n");
	ft_printf(WHITE"CMD[%d] = ",i++);
	while (lst)
	{
		if (lst->type == WORD)
			ft_printf(GREEN"[%s__WORD__]"RESET, lst->word);
		else if (lst->type == PIPE)
		{
			ft_printf(PINK"[%s__PIPE__]"RESET, lst->word);
			ft_printf("\n\n");
			ft_printf(WHITE"CMD[%d] = ",i++);
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

t_lexer	*syntax_error(t_lexer *lexer, t_lexer **lexer_head)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(lexer->word, 2);
	ft_putstr_fd("'\n", 2);
	free_lexer_list(lexer_head);
	return (NULL);
}

// Check validity of lexer tokens in the input
t_lexer	*check_valid_input(t_lexer **lexer_head)
{
	t_lexer	*lexer;
	int		i;

	lexer = *lexer_head;
	i = 0;
	if (!lexer)
		return (NULL);
	while (lexer)
	{
		if (lexer->type == 1 && !i)
			return (syntax_error(lexer, lexer_head));
		if (lexer->type >= 1 && lexer->type <= 5 && lexer->next)
		{
			if ((lexer->next->type >= 1 && lexer->next->type < 5))
				return (syntax_error(lexer, lexer_head));
		}
		else if (lexer->type == LESS_LESS
			&& (!lexer->next || lexer->next->type != WORD))
			return (syntax_error(lexer, lexer_head));
		if (!lexer->next && lexer->type && lexer->type <= 5)
			return (syntax_error(lexer, lexer_head));
		i++;
		lexer = lexer->next;
	}
	return (*lexer_head);
}

// Perform lexical analysis on the input line
t_lexer	*ft_lexer(char *line)
{
	t_lexer *lexer_list;
	char	*epur_line;

	lexer_list = NULL;
	epur_line = ft_epur_str(line);
	ft_printf("epur_str = [%s]\n", epur_line);
	if (ft_fill_lexer(&lexer_list, epur_line))
	{
		free (epur_line);
		free_lexer_list(&lexer_list);
		return (NULL);
	}
	// print_lexer(&lexer_list);
	free(epur_line);
	return (check_valid_input(&lexer_list));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/15 11:24:48 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_cmd(t_lexer *lex)
{
	int	i;

	i = 0;
	if (lex)
		i = 1;
	while (lex)
	{
		if (lex->type == PIPE)
			i ++;
		lex = lex->next;
	}
	return (i);
}

// A VOIR STRUCT VS STUCTURE !!!

t_cmd	**init_cmd_struct(t_lexer **lexer)
{
	t_cmd	**cmd_struct_tab;
	int		cmd_nb;
	int		i;

	i = 0;
	cmd_nb = count_cmd(*lexer);
	cmd_struct_tab = malloc(sizeof(t_cmd *) * (cmd_nb + 1));
	if (!cmd_struct_tab)
		return (NULL);
	while (i < cmd_nb)
	{
		cmd_struct_tab[i] = malloc(sizeof (t_cmd));
		if (!cmd_struct_tab[i])
			return (ft_free_tab((void **)cmd_struct_tab), NULL);
		ft_memset(cmd_struct_tab[i], 0, sizeof(t_cmd)); // + 1 ???
		i ++;
	}
	if (i)
		cmd_struct_tab[i] = NULL;
	return (cmd_struct_tab);
}

// need to send the pointer to the given lexer node
// count the nb of a specific token in a given command
int		token_nb(t_lexer **lexer, t_tokens token)
{
	t_lexer	*lex;
	int		tok_nb;

	lex = *lexer;
	tok_nb = 0;
	if (token == PIPE)
		return (count_cmd(lex));
	while (lex && lex->type != PIPE)
	{
		if (lex->type == token)
			tok_nb++;
		lex = lex->next;
	}
	return (tok_nb);
}
/***********************************************************************************************************/
// fill the char **cmd with the WORD nodes
t_cmd	**fill_cmd_tab(t_lexer **lexer, t_cmd **cmd_struct_tab)
{
	t_lexer	*lex;
	int		i;
	int		j;
	int		tok_nb;
	int		cmd_nb;

	lex = *lexer;
	i = 0;
	j = 0;
	cmd_nb = count_cmd(lex);

	while (i < cmd_nb)
	{
		tok_nb = token_nb(&lex, WORD);
		if (tok_nb)
		{
			cmd_struct_tab[i]->cmd = malloc(sizeof(char *) * (tok_nb + 1));
			if (!cmd_struct_tab[i]->cmd)
				return (ft_free_tab((void **)cmd_struct_tab), NULL);
			while (lex && lex->type != PIPE)
			{
				if (lex->type == WORD)
				{
					cmd_struct_tab[i]->cmd[j] = ft_strdup(lex->word);
					j++;
				}
				lex = lex->next;
			}
			cmd_struct_tab[i]->cmd[j] = NULL;
			if (lex && lex->type == PIPE)
				lex = lex->next;
		}
		j = 0;
		i++;
	}
	return (cmd_struct_tab);
}
/**************************************************************************************************************************/
t_cmd	**init_cmd_structure(t_lexer **lexer, t_cmd **cmd_struct_tab)
{
	t_lexer	*lex;
	int		i;
	int		tok_nb;
	int		cmd_nb;

	lex = *lexer;
	i = 0;
	cmd_nb = count_cmd(lex);
	while (i < cmd_nb && lex)
	{
		tok_nb = token_nb(&lex, WORD);
		if (tok_nb)
		{
			cmd_struct_tab[i]->cmd = malloc(sizeof(char *) * (tok_nb + 1));
			if (!cmd_struct_tab[i]->cmd)
				return (ft_free_tab((void **)cmd_struct_tab), NULL);
			ft_memset(cmd_struct_tab[i]->cmd, 0, tok_nb + 1);
		}
		lex = lex->next;
		i++;
	}
	return (cmd_struct_tab);
}

void	populate_cmd_words(t_lexer **lexer, t_cmd **cmd_struct_tab)
{
	t_lexer	*lex;
	int		i;
	int		j;
	int		cmd_nb;
	int		tok_nb;

	lex = *lexer;
	i = 0;
	cmd_nb = count_cmd(lex);
	while (i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, WORD);
		while (lex && lex->type != PIPE && j < tok_nb)
		{
			if (lex->type == WORD && cmd_struct_tab[i]->cmd)
			{
				cmd_struct_tab[i]->cmd[j] = ft_strdup(lex->word);
				j++;
			}
			lex = lex->next;
		}
		if (cmd_struct_tab[i]->cmd)
			cmd_struct_tab[i]->cmd[j] = NULL;
		if (lex && lex->type == PIPE)
			lex = lex->next;
		i++;
	}
}

// t_cmd	**fill_cmd_tab(t_lexer **lexer, t_cmd **cmd_struct_tab)
// {
// 	if (!init_cmd_structure(lexer, cmd_struct_tab))
// 		return (NULL);
// 	populate_cmd_words(lexer, cmd_struct_tab);
// 	return (cmd_struct_tab);
// }

/***************************************/
/******************EOF******************/
/***************************************/

// t_cmd	**init_eof_structure(t_lexer **lexer, t_cmd **cmd_struct_tab)
// {
// 	t_lexer	*lex;
// 	int		i;
// 	int		tok_nb;

// 	lex = *lexer;
// 	i = 0;
// 	while (i < count_cmd(lex))
// 	{
// 		tok_nb = token_nb(&lex, LIMITER);
// 		if (tok_nb)
// 		{
// 			cmd_struct_tab[i]->eof = malloc(sizeof(char *) * (tok_nb + 1));
// 			if (!cmd_struct_tab[i]->eof)
// 				return (ft_free_tab((void **)cmd_struct_tab), NULL);
// 		}
// 		i++;
// 	}
// 	return (cmd_struct_tab);
// }

// void	populate_eof_words(t_lexer **lexer, t_cmd **cmd_struct_tab)
// {
// 	t_lexer	*lex;
// 	int		i;
// 	int		j;

// 	lex = *lexer;
// 	i = 0;
// 	while (i < count_cmd(lex))
// 	{
// 		j = 0;
// 		while (lex && lex->type != PIPE)
// 		{
// 			if (lex->type == LIMITER)
// 			{
// 				cmd_struct_tab[i]->eof[j] = ft_strdup(lex->word);
// 				j++;
// 			}
// 			lex = lex->next;
// 		}
// 		if (cmd_struct_tab[i]->eof)
// 			cmd_struct_tab[i]->eof[j] = NULL;
// 		if (lex && lex->type == PIPE)
// 			lex = lex->next;
// 		i++;
// 	}
// }

// t_cmd	**fill_eof_tab(t_lexer **lexer, t_cmd **cmd_struct_tab)
// {
// 	if (!init_eof_structure(lexer, cmd_struct_tab))
// 		return (NULL);
// 	populate_eof_words(lexer, cmd_struct_tab);
// 	return (cmd_struct_tab);
// }

/*********************************/
/*********************************/
/*********************************/


t_cmd	**command_builder(t_lexer **lexer)
{
	t_cmd	**cmd_struct_tab;

	cmd_struct_tab = init_cmd_struct(lexer);
	fill_cmd_tab(lexer, cmd_struct_tab);
	// fill_eof_tab(lexer, cmd_struct_tab);
	ft_print_struct_tab(cmd_struct_tab);
	// ft_print_tab((void **)cmd_struct_tab[0]->cmd, "cmd");
	return (cmd_struct_tab);

}

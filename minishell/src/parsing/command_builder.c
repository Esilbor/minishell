/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/30 10:13:11 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fill the char **cmd with the WORD nodes
t_cmd	**fill_cmd_tab(t_lexer *lex, t_cmd **struct_tab, int cmd_nb, int tok_nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, WORD) + token_nb(&lex, EXPAND);
		struct_tab[i]->cmd = malloc(sizeof(char *) * (tok_nb + 1));
		if (!struct_tab[i]->cmd)
			return (ft_free_tab((void **)struct_tab), NULL);
		while (lex && lex->type != PIPE)
		{
			if (lex->type == WORD || lex->type == EXPAND)
			{
				struct_tab[i]->cmd[j] = ft_strdup(lex->word);
				j++;
			}
			struct_tab[i]->cmd[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

t_cmd	**fill_input_lst(t_lexer *lex, t_cmd **struct_tab, int cmd_nb)
{
	int	i;

	i = -1;
	while (++i < cmd_nb)
	{
		while (lex && lex->type != PIPE)
		{
			if (lex->type == INPUT || lex->type == LIMITER)
				ft_add_lex_node(&(struct_tab[i])->input, lex->word, lex->type);
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

t_cmd	**fill_output_lst(t_lexer *lex, t_cmd **struct_tab, int cmd_nb)
{
	int	i;

	i = -1;
	while (++i < cmd_nb)
	{
		while (lex && lex->type != PIPE)
		{
			if (lex->type == OUTPUT || lex->type == APPEND)
				ft_add_lex_node(&(struct_tab[i])->output, lex->word, lex->type);
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

// Initialize an array of command structures from lexer
t_cmd	**init_cmd_struct(t_lexer **lexer)
{
	t_cmd	**cmd_tab;
	int		cmd_nb;
	int		i;

	i = 0;
	cmd_nb = count_cmd(*lexer);
	cmd_tab = malloc(sizeof(t_cmd *) * (cmd_nb + 1));
	if (!cmd_tab)
		return (NULL);
	while (i < cmd_nb)
	{
		cmd_tab[i] = malloc(sizeof (t_cmd));
		if (!cmd_tab[i])
			return (ft_free_tab((void **)cmd_tab), NULL);
		ft_memset(cmd_tab[i], 0, sizeof(t_cmd));
		i ++;
	}
	if (i)
		cmd_tab[i] = NULL;
	return (cmd_tab);
}

// Builds command structures from a lexer and fills them with redirections
t_cmd	**command_builder(t_lexer **lexer)
{
	t_cmd	**cmd_tab;
	int		cmd_nb;
	int		tok_nb;

	tok_nb = 0;
	cmd_nb = count_cmd(*lexer);
	cmd_tab = init_cmd_struct(lexer);
	fill_cmd_tab(*lexer, cmd_tab, cmd_nb, tok_nb);
	fill_input_lst(*lexer, cmd_tab, cmd_nb);
	fill_output_lst(*lexer, cmd_tab, cmd_nb);
	return (cmd_tab);
}

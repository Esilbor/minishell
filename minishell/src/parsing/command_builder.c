/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/21 14:27:38 by esilbor          ###   ########.fr       */
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
				struct_tab[i]->cmd[j++] = ft_strdup(lex->word);
			struct_tab[i]->cmd[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

// fill the char **cmd with the WORD nodes
t_cmd	**fill_eof_tab(t_lexer *lex, t_cmd **struct_tab, int cmd_nb, int tok_nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, LIMITER);
		struct_tab[i]->eof = malloc(sizeof(char *) * (tok_nb + 1));
		if (!struct_tab[i]->eof)
			return (ft_free_tab((void **)struct_tab), NULL);
		while (lex && lex->type != PIPE)
		{
			if (lex->type == LIMITER)
				struct_tab[i]->eof[j++] = ft_strdup(lex->word);
			struct_tab[i]->eof[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

// Allocates and assigns input redirections for each command in struct_tab
t_cmd	**fill_input_tab(t_lexer *lex, t_cmd **stct_tab, int cmd_nb, int tok_nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, INPUT);
		stct_tab[i]->input_redir = malloc(sizeof(char *) * (tok_nb + 1));
		if (!stct_tab[i]->input_redir)
			return (ft_free_tab((void **)stct_tab), NULL);
		while (lex && lex->type != PIPE)
		{
			if (lex->type == INPUT)
				stct_tab[i]->input_redir[j++] = ft_strdup(lex->word);
			stct_tab[i]->input_redir[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (stct_tab);
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

// Builds command structures from a lexer and fills them with redirections
t_cmd	**command_builder(t_lexer **lexer)
{
	t_cmd	**cmd_struct_tab;
	int		cmd_nb;
	int		tok_nb;

	tok_nb = 0;
	cmd_nb = count_cmd(*lexer);
	cmd_struct_tab = init_cmd_struct(lexer);
	fill_cmd_tab(*lexer, cmd_struct_tab, cmd_nb, tok_nb);
	fill_eof_tab(*lexer, cmd_struct_tab, cmd_nb, tok_nb);
	fill_input_tab(*lexer, cmd_struct_tab, cmd_nb, tok_nb);
	// fill_output_tab(*lexer, cmd_struct_tab, cmd_nb, tok_nb);
	fill_output_lst(*lexer, cmd_struct_tab, cmd_nb);
	ft_print_struct_tab(cmd_struct_tab); // IMPRIMER LES TABLEAUX DE COMMANDE
	return (cmd_struct_tab);
}

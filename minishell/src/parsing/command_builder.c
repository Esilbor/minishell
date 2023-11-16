/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:12:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/16 23:02:08 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_lexer *lex)
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
		ft_memset(cmd_struct_tab[i], 0, sizeof(t_cmd));
		i ++;
	}
	if (i)
		cmd_struct_tab[i] = NULL;
	return (cmd_struct_tab);
}

// need to send the pointer to the given lexer node
// count the nb of a specific token in a given command
int	token_nb(t_lexer **lexer, t_tokens token)
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

t_cmd	**fill_input_tab(t_lexer *lex, t_cmd **struct_tab, int cmd_nb, int tok_nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, INPUT);
		struct_tab[i]->input_redir = malloc(sizeof(char *) * (tok_nb + 1));
		if (!struct_tab[i]->input_redir)
			return (ft_free_tab((void **)struct_tab), NULL);
		while (lex && lex->type != PIPE)
		{
			if (lex->type == INPUT)
				struct_tab[i]->input_redir[j++] = ft_strdup(lex->word);
			struct_tab[i]->input_redir[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

t_cmd	**fill_output_tab(t_lexer *lex, t_cmd **struct_tab, int cmd_nb, int tok_nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cmd_nb)
	{
		j = 0;
		tok_nb = token_nb(&lex, OUTPUT) + token_nb(&lex, APPEND);
		struct_tab[i]->output_redir = malloc(sizeof(char *) * (tok_nb + 1));
		if (!struct_tab[i]->output_redir)
			return (ft_free_tab((void **)struct_tab), NULL);
		while (lex && lex->type != PIPE)
		{
			if (lex->type == OUTPUT || lex->type == APPEND)
				struct_tab[i]->output_redir[j++] = ft_strdup(lex->word);
			struct_tab[i]->output_redir[j] = NULL;
			lex = lex->next;
		}
		if (lex && lex->type == PIPE)
			lex = lex->next;
	}
	return (struct_tab);
}

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
	fill_output_tab(*lexer, cmd_struct_tab, cmd_nb, tok_nb);
	ft_print_struct_tab(cmd_struct_tab); // IMPRIMER LES TABLEAUX DE COMMANDE
	// ft_printf("VERIF OK\n");
	// ft_print_tab((void **)cmd_struct_tab[1]->output_redir, "verif_output");

	return (cmd_struct_tab);
}

// Il se passe quelque chose de tres etrange, si le TYPE n'est pas present dans
// la cmd[n] elle ne sera plus jamais rempli pour les autres cmd suivantes

// Candy_$hell> >file1 SEGFAULT

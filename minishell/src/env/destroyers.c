/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:03:51 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 10:04:33 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quit_shell(t_env *envb, t_cmd **cmd_struct_tab)
{
	rl_clear_history();
	ft_printf("exit\n"RESET);
	ft_free_env_lst(envb);
	free_cmd_struct_tab(cmd_struct_tab);
}

void	free_cmd_struct_tab(t_cmd **cmd_struct_tab)
{
	int	i;

	i = 0;
	if (cmd_struct_tab)
	{
		while (cmd_struct_tab[i])
		{
			if (cmd_struct_tab[i]->cmd)
				ft_free_tab((void **)cmd_struct_tab[i]->cmd);
			if (cmd_struct_tab[i]->eof)
				ft_free_tab((void **)cmd_struct_tab[i]->eof);
			if (cmd_struct_tab[i]->input_redir)
				ft_free_tab((void **)cmd_struct_tab[i]->input_redir);
			if (cmd_struct_tab[i]->output)
				free_lexer_list(&(cmd_struct_tab[i])->output);
			if (cmd_struct_tab[i]->heredoc_path)
				free(cmd_struct_tab[i]->heredoc_path);
			i++;
		}
		ft_free_tab((void **)cmd_struct_tab);
	}
}

void	free_shell(t_set *set, char *input, t_cmd **cmd_struct_tab)
{
	ft_free_tab((void **)set->paths);
	ft_free_tab((void **)set->envp);
	free(set);
	free_cmd_struct_tab(cmd_struct_tab);
	free(input);
}

void	candy_crush(t_set *set)
{
	if (set->env_lst)
		ft_free_env_lst(set->env_lst);
	ft_free_tab((void **)set->envp);
	ft_free_tab((void **)set->paths);
	free_cmd_struct_tab(set->cmd_set);
	free (set);
}

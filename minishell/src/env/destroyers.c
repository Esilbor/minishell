/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:03:51 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/06 14:17:37 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// closes pipe file descriptors if exist
void	ft_close_pipes(t_set *set)
{
	if (set->pipe[0][0])
		close(set->pipe[0][0]);
	if (set->pipe[0][1])
		close(set->pipe[0][1]);
	if (set->pipe[1][0])
		close(set->pipe[1][0]);
	if (set->pipe[1][1])
		close(set->pipe[1][1]);
}

void	ft_close_and_free(t_set *set)
{
	if (set->pipe)
	{
		// ft_close_pipes(set); //????
		free(set->pipe[0]);
		free(set->pipe[1]);
		free(set->pipe);
	}
	candy_crush(set);
}

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
			// if (cmd_struct_tab[i]->eof)
			// 	ft_free_tab((void **)cmd_struct_tab[i]->eof);
			// if (cmd_struct_tab[i]->input_redir)
			// 	ft_free_tab((void **)cmd_struct_tab[i]->input_redir);
			if (cmd_struct_tab[i]->output)
				free_lexer_list(&(cmd_struct_tab[i])->output);
			if (cmd_struct_tab[i]->input)
				free_lexer_list(&(cmd_struct_tab[i])->input);
			if (cmd_struct_tab[i]->heredoc_path)
				free(cmd_struct_tab[i]->heredoc_path);
			i++;
		}
		ft_free_tab((void **)cmd_struct_tab);
	}
}

void	free_shell(t_set *set, char *input, t_cmd **cmd_struct_tab)
{
	// ft_free_tab((void **)set->paths); //segf
	// ft_free_tab((void **)set->envp);
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

//close pipes, pid_tab + candy-crush + exit
void	close_crush_exit(char *msg, t_set *set, int do_exit, int exit_ret)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_close_pipes(set);
	ft_free_tab((void **)set->pid);
	candy_crush(set);
	if (do_exit)
		exit(exit_ret);
}

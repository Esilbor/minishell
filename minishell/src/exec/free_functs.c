/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:10:34 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/26 16:15:11 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redirections(t_cmd **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->input)
		{
			if (tab[i]->input->type == LIMITER)
				unlink(tab[i]->input->word);
			free_lexer_list(&tab[i]->input);
		}
		if (tab[i]->output)
			free_lexer_list(&tab[i]->output);
		i++;
	}
}

void	free_cmds(t_cmd **cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_tab[i])
	{
		j = 0;
		while (cmd_tab[i]->cmd[j])
		{
			free (cmd_tab[i]->cmd[j]);
			j++;
		}
		free (cmd_tab[i]->cmd);
		free(cmd_tab[i]);
		i++;
	}
	free (cmd_tab);
	cmd_tab = NULL;
}

void	free_cmd_struct_tab(t_cmd **cmd_tab)
{
	int	i;
	int	j;

	i = -1;
	if (cmd_tab)
	{
		while (cmd_tab[++i])
		{
			if (cmd_tab[i]->output)
				free_lexer_list(&(cmd_tab[i])->output);
			if (cmd_tab[i]->input)
				free_lexer_list(&(cmd_tab[i])->input);
			if (cmd_tab[i]->heredoc_path)
				free(cmd_tab[i]->heredoc_path);
			if (cmd_tab[i]->cmd)
			{
				j = 0;
				while (cmd_tab[i]->cmd[j])
					free(cmd_tab[i]->cmd[j++]);
				free (cmd_tab[i]->cmd);
			}
			free (cmd_tab[i]);
		}
		free (cmd_tab);
	}
}
void	free_after_builtin(t_set *set)
{
	ft_free_env_lst(set->env_lst);
	free(set->pipe[0]);
	free(set->pipe[1]);
	free(set->pipe);
	ft_free_tab((void **)set->paths);
	ft_free_tab((void **)set->envp);
	free_cmds((t_cmd **)set->cmd_set);
	//free(set->pid);
	free (set);
}

void	exit_err(t_set *set, int err_nb)
{
	ft_close_pipes(set);
	free_redirections(set->cmd_set);
	free_after_builtin(set);
	exit(err_nb);
}
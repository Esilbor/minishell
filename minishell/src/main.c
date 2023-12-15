/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/15 20:00:10 by bbresil          ###   ########.fr       */
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

void	sugar_rush(t_set *set)
{
	free(set->pid);
	free(set->pipe[0]);
	free(set->pipe[1]);
	free(set->pipe);
	ft_free_tab((void **) set->paths);
	ft_free_tab((void **) set->envp);
	free_redirections(set->cmd_set);
	free_cmds((t_cmd **)set->cmd_set);
	free(set);
}

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);
	sugar_rush(set);
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
}

void	free_cmd_struct_tab(t_cmd **cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_tab)
	{
		while (cmd_tab[i])
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
				{
					free(cmd_tab[i]->cmd[j]);
					j++;
				}
				free (cmd_tab[i]->cmd);
			}
			free (cmd_tab[i]);
			i++;
		}
		free (cmd_tab);
	}
}

int	shell_loop(t_env *envb)
{
	t_lexer	*lexer;
	char	*input;
	t_cmd	**cmd_tab;
	t_set	*set;

	set = NULL;
	cmd_tab = NULL;
	while (1)
	{
		input = ft_prompt(envb);
		if (input && input[0] && !shell_parser(input, &lexer, envb, &cmd_tab))
		{
			if (cmd_tab[0]->cmd[0])
			{
				execution(set, cmd_tab, envb);
				free(input);
			}
		}
		else if (input)
		{
			continue ;
		}
		else
		{
			ft_printf("exit\n"RESET);
			rl_clear_history();
			ft_free_tab((void **)set->cmd_set);

			// free_redirections(set->cmd_set);
			ft_free_env_lst(envb);
			// ft_free_tab((void **)set->paths);
			// ft_free_tab((void **)set->envp);
			// free_cmds((t_cmd **)set->cmd_set);
			// free(set->pid);
			free (set);
			// free_after_builtin(set); // a renomer
			return (2);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd(PINK"better without added sugar\n"RESET, 2), 1);
	ft_handle_signals();
	envb = get_env(envp);
	shell_loop(envb);
	return (0);
}

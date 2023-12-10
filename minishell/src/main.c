/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/10 21:38:25 by esilbor          ###   ########.fr       */
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
			free_lexer_list(&tab[i]->input);
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
	ft_printf("START OF EXECUTION\n*--------------------------------------------------*\n");
	init_set(&set, cmd_struct_tab, envb); // PROTECT ALL THESE FUNCTIONS WITH IF if they fail
	init_pipe_set(set);
	init_pid_tab(set);
	ft_printf("START OF PIPEX\n*--------------------------------------------------*\n");
	ft_pipex(set);
	ft_printf("END OF PIPEX\n*--------------------------------------------------*\n");
	sugar_rush(set);
	ft_printf("END OF EXECUTION\n*--------------------------------------------------*\n");
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
	t_cmd	**cmd_struct_tab;
	t_set	*set;

	set = NULL;
	cmd_struct_tab = NULL;
	while (1)
	{
		input = ft_prompt(envb);
		if (input && input[0])
		{
			/* if (! */shell_parser(input, &lexer, envb, &cmd_struct_tab)/* ) */;
				// EXIT D
			execution(set, cmd_struct_tab, envb);
			free(input); // EXIT C
			ft_printf("END OF INPUT\n********************************************************\n");
		}
		else if (input) // when enter is pressed without user input
		{
			continue ;
		}
		else // when user ctrl +d
		{
			ft_printf("Ctrl + D pressed\n");
			rl_clear_history();
			ft_free_env_lst(envb);
			// free_after_builtin(set);
			// free_cmds(cmd_struct_tab);
			// free(set);
			ft_printf("exit\n"RESET);
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
	// add_shlvl(envb);
	shell_loop(envb);
	ft_printf("END OF SHELL_LOOP\n********************************************************\n");
	
	return (0);
}

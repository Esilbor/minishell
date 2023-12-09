/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/09 15:56:31 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	// cd, exit, export, unset (source: Oceane)
	init_set(&set, cmd_struct_tab, envb); // PROTECT ALL THESE FUNCTIONS WITH IF if they fail
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);
	sugar_rush(set);
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
			if (!shell_parser(input, &lexer, envb, &cmd_struct_tab))
				// EXIT D
			execution(set, cmd_struct_tab, envb);
			free(input); // EXIT C
		}
		else if (input)
		{
			// sugar_rush(set);
			// ft_quit_shell(set, envb, cmd_struct_tab);
			continue ;
		}
		else
		{
			ft_printf("Ctrl + D pressed\n");
			ft_quit_shell(set, envb, cmd_struct_tab);
			return (2); // EXIT A
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;

	if (argc != 1)
		return (ft_putstr_fd(PINK"better without added sugar\n"RESET, 2), 1);
	(void)argv;
	ft_handle_signals();
	envb = get_env(envp);
	// add_shlvl(envb);
	return (shell_loop(envb));
}

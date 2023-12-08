/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/08 21:47:53 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	// cd, exit, export, unset (source: Oceane)
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);

	//free pid_tab
	//free pipe_set
	// candy_crush
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
			shell_parser(input, &lexer, envb, &cmd_struct_tab);
			execution(set, cmd_struct_tab, envb);
			free_shell(NULL, input, NULL);
		}
		else if (input)
			continue ;
		else
			return (ft_quit_shell(set, envb, cmd_struct_tab), 2);
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
	return (shell_loop(envb));
}

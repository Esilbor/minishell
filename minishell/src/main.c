/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 18:02:10 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{

	// cd, exit, export, unset quand ils sont seuls sont execute dans le parent, lorsqu'il sont en pipe ils sont execute dans le child (source: Oceane)
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);



	// while (set->cmd_set[i] && set->cmd_set[i]->cmd[0])
	// {
	// 	do_builtins(set, i);
	// 	i++;
	// }


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
	// input = ft_prompt(envb); // when launching minishell inside minishell ... to check
	while (1)
	{
		input = ft_prompt(envb);
		if (input && input[0])
		{
			shell_parser(input, &lexer, envb, &cmd_struct_tab);
			execution(set, cmd_struct_tab, envb);
			free_shell(NULL, input, NULL); //should free input? //put cmd_struct_tab to null... no need to be free here?
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
	// shell_loop(envb);
	return (shell_loop(envb));
}

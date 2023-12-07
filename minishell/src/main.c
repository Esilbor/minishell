/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 07:24:01 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
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
	input = ft_prompt(envb);
	if (input)
	{
		shell_parser(input, &lexer, envb, &cmd_struct_tab);
		execution(set, cmd_struct_tab, envb);
		free_shell(set, input, cmd_struct_tab); //should free input?
	}
	else
		return (ft_quit_shell(envb, cmd_struct_tab), 2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;
	int		status;

	if (argc != 1)
		return (ft_putstr_fd("better without added sugar\n", 2), 1);
	(void)argv;
	ft_handle_signals();
	envb = get_env(envp);
	while (1)
	{
		status = shell_loop(envb);
		if (status == 1)
			continue ;
		if (status == 2)
			break ;
	}
	return (0);
}

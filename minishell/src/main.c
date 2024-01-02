/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2024/01/02 22:18:34 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_cmd_tab(t_cmd **cmd_tab)
{
	free_redirections(cmd_tab);
	free_cmd_struct_tab(cmd_tab);
}

//int	shell_loop(t_env *envb)
int	shell_loop(t_set *set, t_cmd **cmd_tab, t_env *envb)
{
	t_lexer	*lexer;
	char	*input;

	while (1)
	{
		ft_handle_signals();
		input = ft_prompt(envb);
		if (input && input[0] && !shell_parser(input, &lexer, envb, &cmd_tab))
		{
			if (cmd_tab[0]->cmd[0][0])
			{
				execution(set, cmd_tab, envb);
				free(input);
			}
			else
				free_cmd_tab(cmd_tab);
		}
		else if (input)
			continue ;
		else
			return (ft_printf("exit\n" RESET), rl_clear_history(),
				ft_free_env_lst(envb), free(set), 2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;
	t_set	*set;
	t_cmd	**cmd_tab;

	set = NULL;
	cmd_tab = NULL;
	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd(PINK "better without added sugar\n" RESET, 2), 1);
	envb = get_env(envp);
	shell_loop(set, cmd_tab, envb);
	return (0);
}

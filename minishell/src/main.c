/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 10:11:40 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Execute built-in commands based on cmd_tab (to be edited)
void	do_builtins(t_set *set, int index)
{
	t_env	**env_dup;

	env_dup = dup_env(&set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "pwd", 4) == 0)
		do_pwd(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "echo", 5) == 0)
		do_echo(ft_tab_len(set->cmd_set[index]->cmd), set->cmd_set[index]->cmd);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "env", 4) == 0)
		print_env(&set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "export", 7) == 0)
	{
		if (set->cmd_set[index]->cmd[1])
			do_export(ft_tab_len(set->cmd_set[index]->cmd),
				set->cmd_set[index]->cmd, &set->env_lst);
		else
			print_env(sort_env(env_dup));
	}
	ft_free_env_lst(*env_dup);
	free(env_dup);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "unset", 6) == 0)
		do_unset(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "cd", 3) == 0)
		do_cd(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0] , "exit", 5) == 0)
		do_exit(set, index);
}

int	shell_parser(char *input, t_lexer **lexer, t_env *envb, t_cmd ***cmd_tab)
{

		parsing(input, lexer, envb);
		if (!(*lexer))
			return (add_history(input), 1);
		*cmd_tab = command_builder(lexer);
		// ft_print_struct_tab(cmd_struct_tab);
		free_lexer_list(lexer);
		return (0);
}

int	shell_loop(t_env *envb)
{
	t_lexer	*lexer;
	char	*input;
	t_cmd	**cmd_struct_tab;
	t_set	*set;
	int		i;

	i = 0;
	cmd_struct_tab = NULL;
	input = ft_prompt(envb);
	if (input)
	{
		shell_parser(input, &lexer, envb, &cmd_struct_tab);
/*************************************************************/
//				EXECUTION PART HERE
		
		init_set(&set, cmd_struct_tab, envb);
		while (set->cmd_set[i] && set->cmd_set[i]->cmd[0])
		{
			do_builtins(set, i);
			i++;
		}
/*************************************************************/
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

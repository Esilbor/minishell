/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 03:00:36 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Handle SIGINT signal and print a prompt
void	sigint_handler(int signum)
{
	(void)signum; // Avoid compiler warning for unused variable
	ft_printf("\001"PINK"\002""\nCandy_Shell> ""\001"YELLOW"\002");
}

void	sigquit_handler(int signum)
{
	(void)signum; // This handler does nothing for SIGQUIT
}
// if (ft_strncmp(cmd_tab[0], "pwd", 4) == 0)

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

void	ft_handle_signals(void)
{
	struct sigaction	sa;
		// Handling SIGINT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure
	sa.sa_handler = sigint_handler; // Assign handler function
	sigaction(SIGINT, &sa, NULL); // Register handler for SIGINT
	// Handling SIGQUIT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure again
	sa.sa_handler = sigquit_handler; // Assign handler function
	sigaction(SIGQUIT, &sa, NULL); // Register handler for SIGQUIT
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
			if (cmd_struct_tab[i]->eof)
				ft_free_tab((void **)cmd_struct_tab[i]->eof);
			if (cmd_struct_tab[i]->input_redir)
				ft_free_tab((void **)cmd_struct_tab[i]->input_redir);
			if (cmd_struct_tab[i]->output)
				free_lexer_list(&(cmd_struct_tab[i])->output);
			if (cmd_struct_tab[i]->heredoc_path)
				free(cmd_struct_tab[i]->heredoc_path);
			i++;
		}
		ft_free_tab((void **)cmd_struct_tab);
	}
}

void	free_shell(char **cmd_tab, t_lexer *lexer, char *input,
	t_cmd **cmd_struct_tab)
{
	ft_free_tab((void **)cmd_tab);
	free_lexer_list(&lexer);
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
		lexer = parsing(input, &lexer, envb);
		if (!lexer)
			return (add_history(input), 1);
		cmd_struct_tab = command_builder(&lexer);
		// ft_print_struct_tab(cmd_struct_tab);
		free_lexer_list(&lexer);
/*************************************************************/
//				EXECUTION PART HERE
		
		init_set(&set, cmd_struct_tab, envb);




//
//
		// if (cmd_struct_tab[0]->cmd[0])
			// do_builtins(cmd_struct_tab[0]->cmd, &envb);
		while (set->cmd_set[i] && set->cmd_set[i]->cmd[0])
		{
			do_builtins(set, i);
			i++;
		}
//
/*************************************************************/
		ft_free_tab((void **)set->paths);
		ft_free_tab((void **)set->envp);
		free(set);
		free_shell(NULL, NULL, input, cmd_struct_tab); //should free input?
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

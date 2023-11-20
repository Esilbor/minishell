/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:06:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/20 19:32:51 by zaquedev         ###   ########.fr       */
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

// Execute built-in commands based on cmd_tab (to be edited)
void	do_builtins(char **cmd_tab, t_env **envb)
{
	t_env	**env_dup;

	env_dup = dup_env(envb);
	if (ft_strcmp(cmd_tab[0], "pwd") == 0)
		do_pwd(cmd_tab, envb);
	if (ft_strcmp(cmd_tab[0], "echo") == 0)
		do_echo(ft_tab_len(cmd_tab), cmd_tab);
	if (ft_strcmp(cmd_tab[0], "env") == 0)
		print_env(envb);
	if (ft_strcmp(cmd_tab[0], "export") == 0)
	{
		if (cmd_tab[1])
			do_export(ft_tab_len(cmd_tab), cmd_tab, envb);
		else
			print_env(sort_env(env_dup));
	}
	ft_free_env_lst(*env_dup);
	free(env_dup);
	if (ft_strcmp(cmd_tab[0], "unset") == 0)
		do_unset(cmd_tab, envb);
	if (ft_strcmp(cmd_tab[0], "cd") == 0)
		do_cd(cmd_tab, envb);
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
			// if (cmd_struct_tab[i]->output_redir)
			// 	ft_free_tab((void **)cmd_struct_tab[i]->output_redir);
			if (cmd_struct_tab[i]->output)
				free_lexer_list(&(cmd_struct_tab[i])->output);
			i++;
		}
		ft_free_tab((void **)cmd_struct_tab);
	}
}

void	free_shell(char **cmd_tab, t_lexer *lexer, char *input, t_cmd **cmd_struct_tab)
{
	ft_free_tab((void **)cmd_tab);
	free_lexer_list(&lexer);
	free_cmd_struct_tab(cmd_struct_tab);
	free(input);
}

int	shell_loop(t_env *envb)
{
	t_lexer	*lexer;
	char	*input;
	char	*cmd_tab_name;
	t_cmd	**cmd_struct_tab;
	t_data *data;

	data = NULL;
	cmd_struct_tab = NULL;
	cmd_tab_name = "tab_name";
	input = ft_prompt(envb);
	if (input)
	{
		lexer = ft_lexer(input);
		if (!lexer)
			return (add_history(input), 1);
		add_history(input);
		// ft_parser(lexer);
		ft_expander(&lexer, envb);
		print_lexer(&lexer); ///
		cmd_struct_tab = command_builder(&lexer);
/*************************************************************/

//				EXECUTION PART HERE

//		cmd_tab = ft_split(input, ' '); // to be deleted
		if (cmd_struct_tab[0]->cmd[0])
			do_builtins(cmd_struct_tab[0]->cmd, &envb);

		// recuperer les cmds



		// print "cmd_struct_tab" = cmd + builtins
		//ft_print_tab((void **)cmd_struct_tab, cmd_tab_name);
		
		
		//ft_execution(data,envb);


/*************************************************************/

		free_shell(NULL, lexer, input, cmd_struct_tab);
	}
	else
		return (ft_quit_shell(envb, cmd_struct_tab), 2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;
	int		status;

	(void)argc;
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

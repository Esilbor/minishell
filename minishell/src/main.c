/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:06:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/02 16:55:13 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum; // Avoid compiler warning for unused variable
	ft_printf(PINK"\nCandy_Shell> "YELLOW);
}

void	sigquit_handler(int signum)
{
	(void)signum; // This handler does nothing for SIGQUIT
}

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

void	ft_quit_shell(t_env *envb)
{
	rl_clear_history();
	ft_printf("exit\n"WHITE);
	ft_free_env_lst(envb);
}

void	free_shell(char **cmd_tab, t_lexer *lexer, char *input)
{
	ft_free_tab((void **)cmd_tab);
	free_lexer_list(&lexer);
	free(input);
}

int	shell_loop(t_env *envb)
{
	t_lexer	*lexer;
	char	*input;
	char	**cmd_tab;

	input = readline(PINK"Candy_$hell> "YELLOW);
	if (input)
	{
		lexer = ft_lexer(input);
		if (!lexer)
			return (add_history(input), 1);
		add_history(input);
		cmd_tab = ft_split(input, ' '); //split the prompt input
		do_builtins(cmd_tab, &envb);
		free_shell(cmd_tab, lexer, input);
	}
	else
		return (ft_quit_shell(envb), 2);
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

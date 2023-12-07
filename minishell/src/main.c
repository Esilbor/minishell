/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/10/25 12:06:41 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/02 16:22:36 by zaquedev         ###   ########.fr       */
=======
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 09:31:57 by esilbor          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
#include "../includes/minishell.h"


// Handle SIGINT signal and print a prompt
void	sigint_handler(int signum)
=======
void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
>>>>>>> main
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

 // a completer avec les signals
int check_first(t_data *data, int argc, char **envp)
{
	if (argc <= 0)
		return (printf("ERR_NOARG"),-1);
	//init_data --> 0;
	if (envp == NULL )
		return (printf("ERR_NOARG"),-1);
	if (data->exit == -1)
		return (printf("ERR_NOARG"),-1);
	//if ft_handle_signals();
	return (0);

	
}


int	shell_loop(t_env *envb, char **envp)
{
	t_lexer	*lexer;
	char	*input;
	t_cmd	**cmd_struct_tab;
<<<<<<< HEAD
	
	t_data *data;

	

	data = NULL;
	cmd_struct_tab = NULL;
	//cmd_tab_name = "tab_name";
	input = ft_prompt(envb);
	if (input)
	{
		lexer = ft_lexer(input);
		if (!lexer)
			return (add_history(input), 1);
		add_history(input);
		ft_expander(&lexer, envb);
		// print_lexer(&lexer); /// PRINT
		if (!lexer)
			return (add_history(input), 1);
		cmd_struct_tab = command_builder(&lexer);
		ft_print_struct_tab(cmd_struct_tab);

		
/*************************************************************/
//				EXECUTION PART HERE


//		cmd_tab = ft_split(input, ' '); // to be deleted
		if (cmd_struct_tab[0]->cmd[0])
			do_builtins(cmd_struct_tab[0]->cmd, &envb);

		// print "cmd_struct_tab" = cmd + builtins
		
printf("\n\n======================= EXECUTION PART HERE ==========================\n");
	

		
		 data = init_set(&data,cmd_struct_tab, envb);
		
		
		// char **envtab;
		// envtab = env_to_tab(envb); // === > ne fonctionne pas !!!
		// printf("envp \n ft_print_char_tab = \n");

		printf("\n======================= data->env_arr = envp ==========================\n");

		data->env_arr = envp;
  		ft_print_char_tab(data->env_arr);
		
			/*
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./minishell
			*/

		printf("\n\ndata->cmds_nb = %d\n", data->cmds_nb);
		int cpt = data->cmds_nb;
		
		// cmd?  ---> cmd_struct_tab[c]->cmd[0])
		int i = 0;
		while (i < cpt)
		{
			printf("cmd_struct_tab[%i]->cmd = %s\n", i, cmd_struct_tab[i]->cmd[0]);
			i++;
		}
		
		// char *set_path_cmd(t_data *data, char *cmd)
		printf("\n\n========main --> set_path_cmd ==================\n\n");

		i = 0;
		while (i < cpt)
		{
			data->cmd_path = set_path_cmd(data,cmd_struct_tab[i]->cmd[0] );
			i++;
		}
		
		/*************************************************************/
		//				TRAITEMENT DES CMD (cmd / builtin)
		//						==> executer un builtin
		//						==> executer une commande (FORK / WAIT / EXECVE)

		
		
		/* 				avant --> cas d'erreurs :
		
			init_data --> 0;
				if (check_first (data->exit , argc , envp) == -1)
					return (1); // exit
					
				if data->exit === -1 --> return (1)
				if envp == -1  --> return (1)
				if argc == -1 --> return (1)

			if (isatty(STDIN_FILENO) == 0)
		 		return (0);
		*/ 
		
		
	
	
		// a completer avec les signals
		// pre-processing // check if exit??? signals ...
		
		if (check_first(data, data->cmds_nb, envp) == -1)
			return (1);
		// parsing the cmds --> stdin ? redirection? pipe?
	
		data->lst_cmd = cmd_struct_tab;
		
		// on considere que tout le parsing est fait ?
		if (!run_execution(data,cmd_struct_tab))
			return (0);

		
	
		
		
		/*************************************************************/
		//				suite du programme


		free_shell(NULL, lexer, input, cmd_struct_tab);
=======
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
			// execution(set, cmd_struct_tab, envb);
			free_shell(NULL, input, NULL); //should free input? //put cmd_struct_tab to null... no need to be free here?
		}
		else if (input)
			continue ;
		else
			return (ft_quit_shell(set, envb, cmd_struct_tab), 2); 
>>>>>>> main
	}
	return (0);
}




//int	main(int argc, t_data *data, char **envp)
int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;
<<<<<<< HEAD
	int		status;
	//t_data	*data;
=======
>>>>>>> main

	if (argc != 1)
		return (ft_putstr_fd("better without added sugar\n", 2), 1);
	(void)argv;
	ft_handle_signals();
	envb = get_env(envp);
<<<<<<< HEAD

	
	while (1)
	{
		status = shell_loop(envb, envp);
		if (status == 1)
			continue ;
		if (status == 2)
			break ;
	}
	return (0);
=======
	return (shell_loop(envb));
>>>>>>> main
}

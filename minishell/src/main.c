/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/12 17:14:03 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redirections(t_cmd **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->input)
			free_lexer_list(&tab[i]->input);
		if (tab[i]->output)
			free_lexer_list(&tab[i]->output);
		i++;
	}
}

void	sugar_rush(t_set *set)
{
	free(set->pid);
	free(set->pipe[0]);
	free(set->pipe[1]);
	free(set->pipe);
	ft_free_tab((void **) set->paths);
	ft_free_tab((void **) set->envp);
	free_redirections(set->cmd_set);
	free_cmds((t_cmd **)set->cmd_set);
	free(set);
}

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);
	sugar_rush(set);
}

void	free_cmds(t_cmd **cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_tab[i])
	{
		j = 0;
		while (cmd_tab[i]->cmd[j])
		{
			free (cmd_tab[i]->cmd[j]);
			j++;
		}
		free (cmd_tab[i]->cmd);
		free(cmd_tab[i]);
		i++;
	}
	free (cmd_tab);
}

void	free_cmd_struct_tab(t_cmd **cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_tab)
	{
		while (cmd_tab[i])
		{
			if (cmd_tab[i]->output)
				free_lexer_list(&(cmd_tab[i])->output);
			if (cmd_tab[i]->input)
				free_lexer_list(&(cmd_tab[i])->input);
			if (cmd_tab[i]->heredoc_path)
				free(cmd_tab[i]->heredoc_path);
			if (cmd_tab[i]->cmd)
			{
				j = 0;
				while (cmd_tab[i]->cmd[j])
				{
					free(cmd_tab[i]->cmd[j]);
					j++;
				}
				free (cmd_tab[i]->cmd);
			}
			free (cmd_tab[i]);
			i++;
		}
		free (cmd_tab);
	}
}
/*
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
*/
/*

int	shell_loop(t_env *envb, char **envp)
{
	t_lexer	*lexer;
	char	*input;
	t_cmd	**cmd_tab;
	t_set	*set;

	set = NULL;
	cmd_tab = NULL;
	while (1)
	{
		input = ft_prompt(envb);
		if (input && input[0] && !shell_parser(input, &lexer, envb, &cmd_tab))
		{
			execution(set, cmd_tab, envb);
			free(input);
		}
		else if (input)
			continue ;
		else
		{
			ft_printf("exit\n"RESET);
			rl_clear_history();
			ft_free_env_lst(envb);
			return (2);
		}
	}
	return (0);
}
*/

/*


//int	main(int argc, t_data *data, char **envp)
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


*/




// void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
// {
// 	// cd, exit, export, unset (source: Oceane)
// 	init_set(&set, cmd_struct_tab, envb);
// 	init_pipe_set(set);
// 	init_pid_tab(set);
// 	ft_pipex(set);

// 	//free pid_tab
// 	//free pipe_set
// 	// candy_crush
// }

// int	shell_loop(t_env *envb)
// {
// 	t_lexer	*lexer;
// 	char	*input;
// 	t_cmd	**cmd_struct_tab;
// 	t_set	*set;

// 	set = NULL;
// 	cmd_struct_tab = NULL;
// 	while (1)
// 	{
// 		input = ft_prompt(envb);
// 		if (input && input[0])
// 		{
// 			shell_parser(input, &lexer, envb, &cmd_struct_tab);
// 			execution(set, cmd_struct_tab, envb);
// 			free_shell(NULL, input, NULL);
// 		}
// 		else if (input)
// 			continue ;
// 		else
// 			return (ft_quit_shell(set, envb, cmd_struct_tab), 2);
// 	}
// 	return (0);
// }
int	shell_loop(t_env *envb)
{
	t_lexer	*lexer;
	char	*input;
	t_cmd	**cmd_tab;
	t_set	*set;

	set = NULL;
	cmd_tab = NULL;
	while (1)
	{
		input = ft_prompt(envb);
		if (input && input[0] && !shell_parser(input, &lexer, envb, &cmd_tab))
		{
			execution(set, cmd_tab, envb);
			free(input);
		}
		else if (input)
			continue ;
		else
		{
			ft_printf("exit\n"RESET);
			rl_clear_history();
			ft_free_env_lst(envb);
			return (2);
		}
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_env	*envb;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd(PINK"better without added sugar\n"RESET, 2), 1);
	ft_handle_signals();
	envb = get_env(envp);
	shell_loop(envb);
	return (0);
}

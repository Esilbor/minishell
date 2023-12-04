/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:02:12 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 17:56:07 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_pipe_close(t_set *set, int index)
{
	close(set->pipe[(index + 1) % 2][0]);
	close(set->pipe[(index + 1) % 2][1]);
}



pid_t	ft_fork(t_set *set, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (printf("ERR_PID\n"));//free close ...
	if (index < set->cmd_nb)
	{
		if (pipe(set->pipe[index % 2]) == -1)
			return (printf("ERR_PIPE\n"));//free close ...
	}
	if (!pid)
	{
		ft_dup2(set, index);
		if (is_builtin(set->cmd_set[index]->cmd))
		{
			do_builtins(set, index);
			// candy_crush et free close ...
			exit(0);
		}
		if (set->cmd_set[index]->cmd[0])
		{
			ft_execve(set, index);
		}
		// candy_crush et free close ...
		exit(1);
	}
	if (index)
		ft_pipe_close(set, index);
	return (pid);
}

void	ft_pipex(t_set *set)
{
	int	i;
	pid_t last_pid;

	i = 0;
	while (i < set->cmd_nb)
	{
		last_pid = ft_fork(set, i);
		// if (!last_pid)
		// 	return;
		set->pid[i] = last_pid;
		i++;
	}
	ft_waidpid(set);
	// if (data->pid)
	// 	free(data->pid);
	candy_crush(set);
}

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	int	i;

	i = 0;
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	init_pid_tab(set);
	ft_pipex(set);



	while (set->cmd_set[i] && set->cmd_set[i]->cmd[0])
	{
		do_builtins(set, i);
		i++;
	}
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

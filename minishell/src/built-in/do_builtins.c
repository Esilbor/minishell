/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:11:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/21 15:58:43 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// faire des writes protegees

int	is_builtin(char **command)
{
	if (!ft_strncmp(command[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(command[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(command[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(command[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(command[0], "export", 7))
		return (1);
	else if (!ft_strncmp(command[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(command[0], "env", 4))
		return (1);
	return (0);
}

// Execute built-in commands based on cmd_tab (to be edited)
void	do_builtins(t_set *set, int index)
{
	t_env	**env_dup;

	env_dup = dup_env(&set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "pwd", 4) == 0)
		do_pwd(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "echo", 5) == 0)
		do_echo(&set->env_lst, set->cmd_set[index]->cmd);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "env", 4) == 0)
		do_env(set, set->env_lst, index);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "export", 7) == 0)
	{
		if (set->cmd_set[index]->cmd[1])
			do_export(ft_tab_len(set->cmd_set[index]->cmd),
				set->cmd_set[index]->cmd, &set->env_lst);
		else
			print_env(set, sort_env(env_dup));
	}
	ft_free_env_lst(*env_dup);
	free(env_dup);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "unset", 6) == 0)
		do_unset(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "cd", 3) == 0)
		do_cd(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "exit", 5) == 0)
		do_exit(set, index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:11:47 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/09 12:16:27 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	failed_write(t_env **env_dup, t_set *set)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free_env_lst(*env_dup);
	free(env_dup);
	exit_err(set, 1);
}

static void	do_builtins2(t_set *set, int index, t_env **env_dup)
{
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "export", 7) == 0)
	{
		if (set->cmd_set[index]->cmd[1])
		{
			if (do_export(ft_tab_len(set->cmd_set[index]->cmd),
					set->cmd_set[index]->cmd, &set->env_lst) < 0)
				failed_write(env_dup, set);
		}
		else
		{
			if (print_env(set, sort_env(env_dup)) < 0)
				failed_write(env_dup, set);
			update_ret(&set->env_lst, 0);
		}
	}
	ft_free_env_lst(*env_dup);
	free(env_dup);
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
		if (do_env(set, set->env_lst, index) < 0)
			failed_write(env_dup, set);
	do_builtins2(set, index, env_dup);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "unset", 6) == 0)
		do_unset(set->cmd_set[index]->cmd, &set->env_lst);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "cd", 3) == 0)
		do_cd(set->cmd_set[index]->cmd, &set->env_lst, set);
	if (ft_strncmp(set->cmd_set[index]->cmd[0], "exit", 5) == 0)
		do_exit(set, index);
}

int	set_home(char **cmd_tab, t_env **envb, char **home)
{
	t_env	*node;

	node = get_env_node(*envb, "HOME");
	if (!node)
	{
		ft_printf("Candy_$hell: cd: %s: No such file or directory\n",
			cmd_tab[1]);
		return (1);
	}
	else
		*home = &node->var_str[5];
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 03:06:36 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	overflow_parsing(const char *str, int *i, int *sign, int *zero_nb)
{
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			(*sign) = -1;
		(*i)++;
	}
	while (str[*i] == '0')
	{
		(*i)++;
		(*zero_nb)++;
	}
}

bool	is_ll_overflow(const char *str)
{
	int		i;
	int		sign;
	int		len;
	int		zero_nb;

	i = 0;
	sign = 1;
	len = 0;
	zero_nb = 0;
	overflow_parsing(str, &i, &sign, &zero_nb);
	while (str[i + len] >= '0' && str[i + len] <= '9')
		len++;
	if ((len > 19) || (len == 19 && sign != -1
			&& ft_strcmp(str + i, MAX_LL) > 0))
		return (true);
	if (len == 19 && sign == -1 && ft_strcmp(str + i, MAX_LL) >= 0)
		return (true);
	return (false);
}

static void	exit_msg(char *arg, int msg)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd("exit: ", 2);
	if (msg == 1)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n"RESET, 2);
		return ;
	}
	ft_putstr_fd("too much sugar\n"RESET, 2);
}

void	exit_parser(t_set *set, char **cmd_tab)
{
	if (ft_tab_len(cmd_tab) > 1 && cmd_tab[1])
	{
		if (!ft_str_isdigit(cmd_tab[1]) || is_ll_overflow(cmd_tab[1]))
		{
			exit_msg(cmd_tab[1], 1);
			candy_crush(set);
			exit (2);
		}
	}
	if (ft_tab_len(cmd_tab) > 2)
	{
		exit_msg(cmd_tab[1], 0);
		candy_crush(set);
		exit (1);
	}
}

// void	do_exit(char **cmd_tab, t_env **env)
void	do_exit(t_set *set, int index)
{
	int	exit_ret;

	exit_ret = 0;
	exit_parser(set, set->cmd_set[index]->cmd);
	if (ft_tab_len(set->cmd_set[index]->cmd) > 1 && set->cmd_set[index]->cmd[1])
	{
		if (ft_atol(set->cmd_set[index]->cmd[1]) > 255)
			exit_ret = ft_atol(set->cmd_set[index]->cmd[1]) % 256;
		else
			exit_ret = ft_atol(set->cmd_set[index]->cmd[1]);
	}
	candy_crush(set);
	exit(exit_ret);
}
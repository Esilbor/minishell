/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/03 20:14:30 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	overflow_parsing(char *str, int *i, int *sign, int *zero_nb)
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
	overflow_parsing((const *) str, &i, &sign, &zero_nb);
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
	ft_putstr_fd(": exit: ", 2);
	if (msg == 1)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required", 2);
		return ;		
	}
	ft_putstr_fd("too many arguments", 2);
}
// check if str is numerical (allow one - or + sign before)
bool str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if ((str[0] == '-' || str[0] == '+') && str[1] && ft_isdigit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_parser(char **cmd_tab)
{
	if (ft_tab_len(cmd_tab) > 1 && cmd_tab[1])
	{
		if (!str_is_digit(cmd_tab[1]) || is_ll_overflow(cmd_tab[1]))
		{
			exit_msg(cmd_tab[1], 1);
			// candy_crush;
			exit (2);
		}
	}
	if (ft_tab_len(cmd_tab) > 2)
	{
		exit_msg(cmd_tab[1], 0);
		// candy_crush;
		exit (1);
	}
}

void	do_exit(char **cmd_tab, t_env **env)
{
	int	exit_ret;

	exit_ret = 0;
	exit_parser(cmd_tab);
	if (ft_tab_len(cmd_tab) > 1  && cmd_tab[1])
	{
		if (ft_atol(cmd_tab[1]) > 255)
			exit_ret = ft_atol(cmd_tab[1]) % 256;
		else
			exit_ret = ft_atol(cmd_tab[1]);
	}
	// candy_crush
	exit(exit_ret);
}

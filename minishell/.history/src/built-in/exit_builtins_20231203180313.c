/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/03 18:03:13 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_ll_overflow(const char *nptr)
{
	int i;
	int sign;
	int	num_len;

	i = 0;
	sign = 1;
	num_len = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))// Skipping leading white spaces
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')// Checking sign
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	int leading_zeroes = 0;	// Counting leading zeroes
	while (nptr[i] == '0')
	{
		i++;
		leading_zeroes++;
	}
	int j = i;
	while (nptr[j] >= '0' && nptr[j] <= '9')// Calculate the length of the number part
	{
		j++;
		num_len++;
	}
	if (num_len > 19 || (num_len == 19 && sign != -1 && strcmp(nptr + i, MAX_LL) > 0))// Length check
		return true; // Overflow
	if (num_len == 19 + 1 && sign == -1 && strcmp(nptr + i, MAX_LL) > 0 && leading_zeroes == 0)
		return true; // Underflow
	return false; // No overflow/underflow
}


static void	exit_msg(char *arg, int msg)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd(": exit: ", 2);
	if (msg = 1)
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
	if ((str[0] == '-' || str[0] == '+') && str[1] && ft_is_digit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	do_exit(char **cmd_tab, t_env **envb)
{
	(void) envb;
	if (ft_tab_len(cmd_tab) > 1 && cmd_tab[1])
	{
		if (!str_is_digit(cmd_tab[1]))
		{
			exit_msg(cmd_tab[1], 1);
			// candy_crush
			exit(2);
		}
	}
	if (ft_tab_len(cmd_tab) > 2)
	{
		exit_msg(cmd_tab[1], 0);
		// candy_crush
		exit(1);
	}
	
	return (0);
}
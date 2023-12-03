/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:11:36 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/03 18:18:30 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static 

bool	is_ll_overflow(const char *str)
{
	int		i;
	int		sign;
	int		num_len;
	int		leading_zeroes;

	i = 0;
	sign = 1;
	num_len = 0;
	leading_zeroes = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
	{
		i++;
		leading_zeroes++;
	}
	while (str[i + num_len] >= '0' && str[i + num_len] <= '9')
		num_len++;
	if ((num_len > 19) || (num_len == 19 && sign != -1 && strcmp(str + i, MAX_LL) > 0))
		return true;
	if (num_len == 19 && sign == -1 && strcmp(str + i, MAX_LL) >= 0)
		return true;
	return false;
}


// bool is_ll_overflow(const char *str)
// {
// 	int i;
// 	int sign;
// 	int	num_len;

// 	i = 0;
// 	sign = 1;
// 	num_len = 0;
// 	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))// Skipping leading white spaces
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')// Checking sign
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	int leading_zeroes = 0;	// Counting leading zeroes
// 	while (str[i] == '0')
// 	{
// 		i++;
// 		leading_zeroes++;
// 	}
// 	int j = i;
// 	while (str[j] >= '0' && str[j] <= '9')// Calculate the length of the number part
// 	{
// 		j++;
// 		num_len++;
// 	}
// 	if (num_len > 19 || (num_len == 19 && sign != -1
// 		&& strcmp(str + i, MAX_LL) > 0))// Length check
// 		return true; // Overflow
// 	if (num_len == 19 && sign == -1 && ft_strcmp(str + i, MAX_LL) >= 0)
// 		return true; // Underflow
// 	return false; // No overflow/underflow
// }


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
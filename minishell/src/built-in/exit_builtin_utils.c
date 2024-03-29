/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:10:03 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/25 18:57:05 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	candy_crush(t_set *set)
{
	if (set->env_lst)
		ft_free_env_lst(set->env_lst);
	ft_free_tab((void **)set->envp);
	ft_free_tab((void **)set->paths);
	free_cmd_struct_tab(set->cmd_set);
	free (set->pipe[0]);
	free (set->pipe[1]);
	free (set->pipe);
	free (set);
}

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

int	exit_parser(char **cmd_tab)
{
	if (ft_tab_len(cmd_tab) > 1 && cmd_tab[1])
	{
		if (!ft_str_isdigit(cmd_tab[1]) || is_ll_overflow(cmd_tab[1]))
		{
			exit_msg(cmd_tab[1], 1);
			return (2);
		}
	}
	if (ft_tab_len(cmd_tab) > 2)
	{
		exit_msg(cmd_tab[1], 0);
		return (1);
	}
	return (0);
}

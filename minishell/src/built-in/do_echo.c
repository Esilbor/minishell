/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/03 11:17:24 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_echo(int cmd_nb, char **str)
{
	int	n_flag;
	int	i;
	int	j;

	n_flag = 1; // By default, echo prints a newline at the end
	i = 1; // Start with the first argument after the "echo" command
	j = 1;
	while (i < cmd_nb && !ft_strncmp(str[i], "-n", 2) // Check for the "-n" option(s)
		&& !ft_strccmp(&str[i][j], 'n'))
	{
		n_flag = 0;
		i++;
	}
	while (i < cmd_nb) // Print the rest of the arguments
	{
		ft_printf(GREEN"%s", str[i]);
		if (i < cmd_nb - 1) {
			ft_printf(" ");	// Print a space between arguments
		}
		i++;
	}
	if (n_flag) // Print a newline if needed
		printf("\n");
}

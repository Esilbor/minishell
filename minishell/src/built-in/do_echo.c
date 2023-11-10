/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/10 16:48:44 by bbresil          ###   ########.fr       */
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
	while (i < cmd_nb && !ft_strncmp(str[i], "-n", 2)
		&& !ft_strccmp(&str[i][j], 'n'))
	{
		n_flag = 0;
		i++;
	}
	while (i < cmd_nb) // Print the rest of the arguments
	{
		// ft_printf(GREEN"%s", str[i]);
		// write(1, str[i], 1);
		ft_putstr_fd(str[i], 1);
		if (i < cmd_nb - 1)
			ft_printf(" "); // Print a space between arguments
		i++;
	}
	if (n_flag) // Print a newline if needed
		printf("\n");
}

// ISSUES

// Candy_Shell> echo -n Candy_Shell
// Candy_ShellCa



/*****ADRIANO'S VERSION****/
// int	ft_echo_option(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '-' && str[i + 1])
// 	{
// 		i++;
// 		while (str[i] && str[i] == 'n')
// 			i++;
// 		if (!str[i])
// 			return (1);
// 	}
// 	return (0);
// }

// void	do_echo(int cmd_nb, char **str)
// {
// 	int	i;

// 	(void)cmd_nb;
// 	i = 1;
// 	if (!str[1])
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	while (str[i] && ft_echo_option(str[i]))
// 		i++;
// 	while (str[i] && str)
// 	{
// 		if (str[i][0] != '\0')
// 		{
// 			printf("%s", str[i]);
// 			if (str[i + 1])
// 				printf(" ");
// 		}
// 		i++;
// 	}
// 	if (!ft_echo_option(str[1]))
// 		printf("\n");
// }

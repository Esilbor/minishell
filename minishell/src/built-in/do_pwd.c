/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:53:11 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/02 13:32:22 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_pwd(char **cmd_tab, t_env **env)
{
	char	*cwd;
	char	buffer[4096]; // A standard buffer size for most systems
	if (cmd_tab[1] && ft_is_c(cmd_tab[1][0], '-'))
	{
		ft_putstr_fd("Candy_$hell: ", 2);
		ft_putchar_fd(cmd_tab[1][0], 2);
		ft_putchar_fd(cmd_tab[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (update_ret(env, 2));
	}
	// Get the current working directory using getcwd()
	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd != NULL)
		printf(CYAN"%s\n", cwd);
	else
		perror("minishell: pwd"); // Print error if getcwd() fails
	return (update_ret(env, 0));
}
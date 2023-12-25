/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo_pwd_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/25 17:36:19 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_echo(t_env **env, char **str)
{
	int	n_flag;
	int	i;
	int	j;
	int cmd_nb;

	//write(2, "echo\n", 6);
	n_flag = 1;
	i = 1;
	j = 1;
	cmd_nb = ft_tab_len(str);
	while (i < cmd_nb && !ft_strncmp(str[i], "-n", 2)
		&& !ft_strccmp(&str[i][j], 'n'))
	{
		n_flag = 0;
		i++;
	}
	while (i < cmd_nb)
	{
		ft_putstr_fd(str[i], 1); // proteger
		if (i < cmd_nb - 1)
			ft_printf(" "); // write et proteger les write
		i++;
	}
	if (n_flag)
		ft_printf("\n");
	return (update_ret(env, 0));
}

int	do_pwd(char **cmd_tab, t_env **env)
{
	char	*cwd;
	char	buffer[4096];

	if (cmd_tab[1] && ft_is_c(cmd_tab[1][0], '-'))
	{
		ft_putstr_fd("Candy_$hell: ", 2);
		ft_putchar_fd(cmd_tab[1][0], 2);
		ft_putchar_fd(cmd_tab[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (update_ret(env, 2));
	}
	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("minishell: pwd");
		return (update_ret(env, 2));
	}
	return (update_ret(env, 0));
}

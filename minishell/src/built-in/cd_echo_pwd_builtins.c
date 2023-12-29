/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo_pwd_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/29 09:15:14 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_protected_write_fd(char *s, int fd, t_env **env)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (write(fd, &s[i], 1) != 1)
			return (update_ret(env, 1));
		i++;
	}
	if (i != ft_strlen2(s))
	{
		ft_putstr_fd ("ERROR WRITE : could not write string to fd\n", 2);
		return (update_ret(env, 1));
	}
	return (0);
}

int	do_echo(t_env **env, char **str)
{
	int	n_flag;
	int	i;
	int	j;
	int	cmd_nb;

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
		ft_protected_write_fd(str[i], 1, env);
		// ft_putstr_fd(str[i], 1); // proteger
		if (i < cmd_nb - 1)
			ft_protected_write_fd(" ", 1, env);
			// ft_printf(" "); // write et proteger les write
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

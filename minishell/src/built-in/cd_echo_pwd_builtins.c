/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo_pwd_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/02 18:14:20 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

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
*/


int	fail_to_write_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (write(fd, &s[i], 1) != 1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		i++;
	}
	return (0);
}

// determine the -n flag's presence and update the index i.
static int	handle_n_flag(char **str, int *i)
{
	int	n_flag;
	int	j;

	n_flag = 1;
	j = 1;
	while (str[*i] && !ft_strncmp(str[*i], "-n", 2)
		&& !ft_strccmp(&str[*i][j], 'n'))
	{
		n_flag = 0;
		(*i)++;
	}
	return (n_flag);
}

// print the strings and handle spaces between them.
static int	print_str(char **str, int i, int cmd_nb, t_env **env)
{
	while (i < cmd_nb)
	{
		if (fail_to_write_fd(str[i], 1)
			|| (i < cmd_nb - 1 && fail_to_write_fd(" ", 1)))
			return (update_ret(env, -1));
		i++;
	}
	return (0);
}

int	do_echo(t_env **env, char **str)
{
	int	n_flag;
	int	i;
	int	cmd_nb;

	i = 1;
	cmd_nb = ft_tab_len(str);
	n_flag = handle_n_flag(str, &i);
	if (print_str(str, i, cmd_nb, env) == -1)
		return (update_ret(env, -1));
	if (n_flag && fail_to_write_fd("\n", 1))
		return (update_ret(env, -1));
	//return (update_ret(env, 0));
	//printf("Dans le fonction do_echo --> g_exit_val  avant update = %d\n", g_exit_val);
	return (update_ret(env, g_exit_val)); // ajout
	
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
	{
		if (fail_to_write_fd(cwd, 1))
			return (update_ret(env, -1));
		if (fail_to_write_fd("\n", 1))
			return (update_ret(env, -1));
	}
	else
	{
		perror("minishell: pwd");
		return (update_ret(env, 2));
	}
	return (update_ret(env, 0));
	//return (update_ret(env, g_exit_val));
}

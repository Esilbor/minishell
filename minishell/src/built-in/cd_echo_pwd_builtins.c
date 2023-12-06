/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo_pwd_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:09:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/06 13:10:42 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_cd(char **str, t_env **envb)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (str[1] == NULL)
	{
		chdir((const char *)get_env_node(*envb, "HOME"));
		free(tmp);
		return (1);
	}
	else if (str[1][0] == '~')
	{
		chdir((const char *)get_env_node(*envb, "HOME"));
		free(tmp);
		return (1);
	}
	else if (chdir(str[1]) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", str[1], strerror(errno));
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

void	do_echo(int cmd_nb, char **str)
{
	int	n_flag;
	int	i;
	int	j;

	n_flag = 1;
	i = 1;
	j = 1;
	while (i < cmd_nb && !ft_strncmp(str[i], "-n", 2)
		&& !ft_strccmp(&str[i][j], 'n'))
	{
		n_flag = 0;
		i++;
	}
	while (i < cmd_nb)
	{
		ft_putstr_fd(str[i], 1);
		if (i < cmd_nb - 1)
			ft_printf(" ");
		i++;
	}
	if (n_flag)
		ft_printf("\n");
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
		ft_printf(CYAN"%s\n", cwd);
	else
		perror("minishell: pwd");
	return (update_ret(env, 0));
}

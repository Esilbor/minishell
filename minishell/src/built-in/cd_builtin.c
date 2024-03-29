/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:28:12 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/10 12:59:19 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_old_pwd(t_env *oldpwd, t_env *pwd, t_set *set)
{
	char	*tmp;

	tmp = ft_strjoin("OLD", pwd->var_str);
	if (!tmp && pwd->var_str)
		exit_err(set, 1);
	if (!tmp && pwd->var_str)
		exit_err(set, 1);
	free(oldpwd->var_str);
	oldpwd->var_str = ft_strdup(tmp);
	if (!oldpwd->var_str)
	{
		free(tmp);
		exit_err(set, 1);
	}
	free(tmp);
}

static void	set_new_pwd(t_env *pwd, t_set *set)
{
	char	*tmp;
	char	*new_pwd;

	tmp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", tmp);
	if (!new_pwd && tmp)
		exit_err(set, 1);
	free(tmp);
	free(pwd->var_str);
	pwd->var_str = ft_strdup(new_pwd);
	if (!pwd->var_str)
	{
		free(new_pwd);
		exit_err(set, 1);
	}
	free(new_pwd);
}

static void	update_pwd(t_env **envb, t_set *set)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = get_env_node(*envb, "PWD");
	oldpwd = get_env_node(*envb, "OLDPWD");
	if (pwd && oldpwd)
	{
		set_old_pwd(oldpwd, pwd, set);
		set_new_pwd(pwd, set);
	}
}

static int	handle_cd(t_env **envb, t_set *set, char *path)
{
	if (is_directory(path) && !chdir(path))
	{
		update_pwd(envb, set);
		return (update_ret(envb, 0));
	}
	else
	{
		ft_printf("Candy_$hell: cd: %s: No such directory or file\n",
			path);
		return (update_ret(envb, 1));
	}
	return (1);
}

int	do_cd(char **cmd_tab, t_env **envb, t_set *set)
{
	char	*home;
	char	*tmp;
	int		ret;

	if (set_home(cmd_tab, envb, &home))
		return (update_ret(envb, 1));
	if (cmd_tab[1] == NULL || (cmd_tab[1][0] == '~' && !cmd_tab[1][1]))
		return (handle_cd(envb, set, home));
	else if (cmd_tab[1][0] == '~' && cmd_tab[1][1] == '/')
	{
		tmp = ft_strjoin(home, &cmd_tab[1][1]);
		ret = handle_cd(envb, set, tmp);
		if (cmd_tab[1] && (!is_directory(tmp)))
		{
			free(tmp);
			ft_printf("Candy_$hell: cd: %s: No such file or directory\n",
				cmd_tab[1]);
			return (update_ret(envb, 1));
		}
		return (free(tmp), ret);
	}
	else if (cmd_tab[1])
		return (handle_cd(envb, set, cmd_tab[1]));
	return (update_ret(envb, 0));
}

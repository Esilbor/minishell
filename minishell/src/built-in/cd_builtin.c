/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:28:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/26 17:59:09 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


	// pwd = get_env_node(*envb, "PWD");
	// oldpwd = get_env_node(*envb, "OLDPWD");
	// tmp = ft_strjoin("OLD", pwd->var_str);
	// free(oldpwd->var_str);
	// oldpwd->var_str = ft_strdup(tmp);
	// free (tmp);
	// tmp = getcwd(NULL, 0);
	// new_pwd = ft_strjoin("PWD=", tmp);
	// free (tmp);
	// free (pwd->var_str);
	// pwd->var_str = ft_strdup(new_pwd);
	// free (new_pwd);

static void	update_pwd(t_env **envb)
{
	char	*tmp;
	t_env	*pwd;
	t_env	*oldpwd;
	char	*new_pwd;

	pwd = get_env_node(*envb, "PWD");
    oldpwd = get_env_node(*envb, "OLDPWD");   
    if (pwd && oldpwd) 
	{
        tmp = ft_strjoin("OLD", pwd->var_str);
        if (oldpwd->var_str)
            free(oldpwd->var_str);
        oldpwd->var_str = ft_strdup(tmp);
        free(tmp);
        tmp = getcwd(NULL, 0);
        if (tmp) 
		{
            new_pwd = ft_strjoin("PWD=", tmp);
            free(tmp);
            if (pwd->var_str) 
                free(pwd->var_str);
            pwd->var_str = ft_strdup(new_pwd);
            free(new_pwd);
        }
    }	
}

int	do_cd(char **cmd_tab, t_env **envb)
{
	char	*tmp;

	if (cmd_tab[1] == NULL || cmd_tab[1][0] == '~')
	{
		tmp = &get_env_node(*envb, "HOME")->var_str[5];
		if (is_directory(tmp) && !chdir(tmp))
			update_pwd(envb);
	}
	else if (cmd_tab[1] && is_directory(cmd_tab[1]) && !chdir(cmd_tab[1]))
		update_pwd(envb);
	else if (cmd_tab[1] && !is_directory(cmd_tab[1]))
	{
		ft_printf("Candy_$hell: cd: %s: No such file or directory\n");
		return (update_ret(envb, 1));
	}
	return (update_ret(envb, 0));
}

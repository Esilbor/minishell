/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/02 18:52:56 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	string_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}

static char	*check_cmd_null(char *cmd)
{
	if (!cmd || string_empty(cmd))
	{
		return (ft_putstr_fd("CMD NULL", 2), NULL);
	}
	return (cmd);
}

//return true if cmd is a directory
bool	is_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf))
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (is_directory(cmd))
		ft_putstr_fd("is a directory\n", 2);
	else
		ft_putstr_fd("cmd_path not found\n", 2);
}

char *set_path_cmd(t_set *set, char *cmd)
{
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	while (set->paths[index] && cmd)
	{
		tmp = ft_strjoin("/", cmd);
		if (!tmp)
			return (free_after_builtin(set),ft_putstr_fd("ERR_MAL\n", 2), NULL); // (1) ---> ?free + close tout ce qui a ete initialise/ malloc avant
		cmd_tmp = ft_strjoin(set->paths[index], tmp);
		if (!cmd_tmp)
			return (free(tmp),free_after_builtin(set),ft_putstr_fd("ERR_MAL\n", 2), NULL); // (2)
		if (access(cmd_tmp, X_OK | F_OK) == 0)		
			return (free(tmp),cmd_tmp);
		free(tmp);
		free (cmd_tmp);
		index++;
	}
	print_cmd_not_found(cmd);
	return (NULL);
}

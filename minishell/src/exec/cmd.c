/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/13 08:33:36 by esilbor          ###   ########.fr       */
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
		//write(STDERR, ERR_CMD, ft_strlen(ERR_CMD));
		//return (NULL);
		return (ft_putstr_fd("CMD NULL", 2), NULL);
	}
	return (cmd);
}

// int	second_chance(t_set *set, char *cmd) // refaire avec just access et return le char* cmd_path
// {
// 	char	**cmd_tab;
// 	char	*cmd_path;

// 	cmd_tab = NULL;
// 	if(ft_strchr(cmd, ' '))
// 		cmd_tab = ft_split(cmd, ' ');
// 	else
// 		return (0);
// 	if (set->paths && (!ft_strchr(cmd_tab[0], '/')))
// 	{
// 		cmd_path = set_path_cmd(set, cmd_tab[0]);
// 		if (!cmd_path)
// 			exit_err(set, 127);
// 		execve(cmd_path, cmd_tab, set->envp);
// 	}
// 	exit_err(set, 126);
// }

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
			return (ft_putstr_fd("ERR_MALLOC\n", 2), NULL); // free!!!
		cmd_tmp = ft_strjoin(set->paths[index], tmp);
		if (!cmd_tmp)
		{
			free(tmp);
			return (ft_putstr_fd("ERR_MALLOC\n", 2), NULL); // free!!!
		}
		if (access(cmd_tmp, X_OK | F_OK) == 0)
		{
			free(tmp);
			return (cmd_tmp);
		}
		free(tmp);
		free (cmd_tmp);
		index++;
	}
	// second_chance(set, cmd);
	print_cmd_not_found(cmd);
	return (NULL);
}

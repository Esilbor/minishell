/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/12 07:07:56 by esilbor          ###   ########.fr       */
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
		return (ft_putstr_fd("ERR_CMD\n", 2), NULL);
	}
	return (cmd);
}

char *set_path_cmd(t_set *set, char *cmd)
{
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	while (set->paths[index])
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
	ft_putstr_fd("cmd_path not found\n", 2);
	return (NULL);
}

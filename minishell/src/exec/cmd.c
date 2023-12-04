/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/04 17:07:20 by bbresil          ###   ########.fr       */
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
		return (printf("ERR_CMD\n"), NULL);
	}
	return (cmd);
}

char *set_path_cmd(t_set *set, char *cmd)
{
	printf("Ici dans fonction set_path_cmd\n ");

	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (printf("ERR_MALLOC\n"), NULL); // free!!!

	while (set->paths[index])
	{
		cmd_tmp = ft_strjoin(set->paths[index], tmp);
		if (!cmd_tmp)
		{
			free(tmp);
			return (printf("ERR_MALLOC\n"), NULL); // free!!!
		}

		if (access(cmd_tmp, X_OK | F_OK) == 0)
		{
			printf("cmd_tmp = %s\n", cmd_tmp);
			return (cmd_tmp);
		}
		free (cmd_tmp);
		index++;
	}
	printf("\ncmd_path not found\n");
	return (NULL);
}

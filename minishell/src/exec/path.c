/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:32:29 by zaquedev          #+#    #+#             */
/*   Updated: 2023/11/20 19:41:05 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


char	*ft_read_path(t_data *data)
{
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (!ft_strncmp("PATH", current->var_str, 5))
			return (current->env_value);
		current = current->next;
	}
	return (NULL);
}


char 	**set_tab_paths(t_data *data)
{
	if (!(data->cmd_path = ft_read_path(data)))
		return (printf("ERR_CMD\n"), NULL);
	if (data->cmd_path)
	{
		data->paths = ft_split(data->cmd_path, ':');
		if(!data->paths)
			return (printf("ERR_SPLIT\n"), NULL); // free!!!
	}
	return(data->paths);
}

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

char *set_cmd_path(t_data *data, char *cmd)
{
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	data->paths = set_tab_paths(data);

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (printf("ERR_MALLOC\n"), NULL); // free!!!
	while (data->paths[index])
	{
		cmd_tmp = ft_strjoin(data->paths[index], tmp);
		if (!cmd_tmp)
		return (printf("ERR_MALLOC\n"), NULL); // free!!!
		free(tmp);
		//cmd_tmp = check_cmd(data, cmd_tmp);
		if (access(cmd_tmp, X_OK | F_OK) == 0)
			return (cmd_tmp);
		free (cmd_tmp);
		index++;
	}
	return (NULL);
}

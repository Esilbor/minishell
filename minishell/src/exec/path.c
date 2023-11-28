/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:32:29 by zaquedev          #+#    #+#             */
/*   Updated: 2023/11/28 18:33:38 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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

// Recuperer la variable PATH a partir de env (environment)

char *ft_get_path(t_env *envb)
{
	t_env *p;
	char *path;

	p = get_env_node(envb, "PATH");
    if (!p || !p->var_str)
        return (NULL);
    path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
    // if(!path)
    //     return (NULL);
	printf("path dans ft_get_path \n=> path = %s\n", path);
	return (path);
}



char *set_path_cmd(t_data *data, char *cmd)
{
	printf("Ici dans fonction set_path_cmd\n ");
	
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	
	//data->paths[0] = ft_get_path(data->lst_env);

	index = 0;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (printf("ERR_MALLOC\n"), NULL); // free!!!

	while (data->paths[index])
	{
		//printf(" ==> data->paths[%d] = %s\n",index, data->paths[index]);
		
		cmd_tmp = ft_strjoin(data->paths[index], tmp);
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


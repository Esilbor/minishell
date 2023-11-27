/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:32:29 by zaquedev          #+#    #+#             */
/*   Updated: 2023/11/27 18:11:41 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


// char	*ft_read_path(t_data *data)
// {
// 	t_env	*current;

// 	current = data->lst_env;
// 	while (current)
// 	{
// 		if (!ft_strncmp("PATH", current->var_str, 5))
// 			return (current->env_value);
// 		current = current->next;
// 	}
// 	return (NULL);
// }


// char 	**set_tab_paths(t_data *data)
// {
// 	if (!(data->cmd_path = ft_read_path(data)))
// 		return (printf("ERR_CMD\n"), NULL);
// 	if (data->cmd_path)
// 	{
// 		data->paths = ft_split(data->cmd_path, ':');
// 		if(!data->paths)
// 			return (printf("ERR_SPLIT\n"), NULL); // free!!!
// 	}
// 	return(data->paths);
// }



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


// char *set_path_cmd(t_data *data ,char **path_to_check, char *cmd)
// {
// 	//int index;
// 	char *tmp;
// 	char *cmd_tmp;

// 	cmd = check_cmd_null(cmd);
// 	//index = 0;
// 	//data->paths = set_tab_paths(data);
// 	path_to_check = ft_get_path(data->lst_env);

// 	tmp = ft_strjoin("/", cmd);
// 	if (!tmp)
// 		return (printf("ERR_MALLOC\n"), NULL); // free!!!
// 	while (path_to_check != NULL && *path_to_check)
// 	{
// 		cmd_tmp = ft_strjoin(path_to_check, tmp);
// 		printf("Ici dans fonction set_path_cmd ===> data->paths[index] = %s\n", *data->paths);
// 		if (!cmd_tmp)
// 			return (printf("ERR_MALLOC\n"), NULL); // free!!!
// 		free(tmp);
// 		//cmd_tmp = check_cmd(data, cmd_tmp);
// 		//printf("cmd_tmp = %s\n", cmd_tmp);
// 		if (access(cmd_tmp, X_OK | F_OK) == 0)
// 		{
//             printf("cmd_tmp = %s\n", cmd_tmp);
//             return (cmd_tmp);
//         }
// 			//return (cmd_tmp);
// 		free (cmd_tmp);
// 		path_to_check++;
// 	}
// 	return (NULL);
// }

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
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;

	data->paths[0] = ft_get_path(data->lst_env);

	

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (printf("ERR_MALLOC\n"), NULL); // free!!!

	while (data->paths != NULL && *data->paths)
	{
		//printf("Ici dans fonction set_path_cmd\n ==> data->paths[%d] = %s\n",index, data->paths[index]);
		
		printf("???\n");
		
		cmd_tmp = ft_strjoin(*data->paths, tmp);
		//printf("cmd_tmp = %s\n", cmd_tmp);
		
		if (!cmd_tmp)
			return (printf("ERR_MALLOC\n"), NULL); // free!!!
		free(tmp);
		if (access(cmd_tmp, X_OK | F_OK) == 0)
		{
            printf("cmd_tmp = %s\n", cmd_tmp);
            return (cmd_tmp);
        }
			//return (cmd_tmp);
		free (cmd_tmp);
		data->paths++;
		index++;
	}
	return (NULL);
}


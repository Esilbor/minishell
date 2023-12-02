/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:42:21 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/02 19:43:33 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int ft_nb_cmd(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}


// void	ft_path_ok_cmd(t_data *data, char **cmd, char **envp, int index)
// {
// 	char	*cmd_find;

// 	printf(" *********** ft_path_ok_cmd **********\n");
// 	cmd_find = set_path_cmd(data, cmd[0]);
// 	if (!cmd_find)
// 	{
// 		//free , exit ?
// 		// ft_free_tab((void **)envp);
// 		printf(" cmd_path //  = %s\n", data->lst_cmd[index]->cmd[0]);
// 		//ft_free_char_tab(envp);
// 	}
// }
 void ft_exec_cmd(t_data *data, int index)
 {

	char	*cmd_find;

	cmd_find = set_path_cmd(data, data->lst_cmd[index]->cmd[0]);
	if (!cmd_find)
	{
		printf(" cmd_path //  = %s\n", data->lst_cmd[index]->cmd[0]);
		//ft_free_char_tab(envp); //free , exit ?
	}
	
	if (data->path && !ft_strchr(cmd_find, '/')) // avec path
	{
		if (execve(cmd_find, data->lst_cmd[index]->cmd, data->env_arr)== -1)
		{
			//if (errno == ? ) 
			printf("candyshell: %s: Permission denied\n", cmd_find);
			printf("candyshell: %s:command not found\n", cmd_find);
			printf("candyshell: %s: No such file or directory\n",cmd_find);
			//free  tab env ...// close pipes
			exit(127);
		}
	}
	else if (access(cmd_find, F_OK | X_OK| R_OK)) // sans path
	{
		if (execve(cmd_find, data->lst_cmd[index]->cmd, data->env_arr)== -1)
		{
			//if (errno == ? ) 
			printf("candyshell: %s: Permission denied\n", cmd_find);
			printf("candyshell: %s:command not found\n", cmd_find);
			printf("candyshell: %s: No such file or directory\n",cmd_find);
			//free // close pipes
			exit(127);
		}
	}
	
 }


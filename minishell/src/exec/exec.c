/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/11/28 19:42:21 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/02 19:43:33 by zaquedev         ###   ########.fr       */
=======
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/07 07:31:25 by esilbor          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int ft_nb_cmd(char *str)
{
<<<<<<< HEAD
	int i;
	int count;
=======
	t_env	*p;
	char	*path;

	p = get_env_node(envb, "PATH");
	if (!p || !p->var_str)
		return (NULL);
	path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
	if (!path)
		return (NULL);
	*set = malloc(sizeof(t_set));
	if (!(*set))
		return (free (path), NULL);
	ft_memset(*set, 0, sizeof(t_set));
	if (cmd_struct_tab && cmd_struct_tab[0])
		(*set)->cmd_nb = ft_tab_len((char **)cmd_struct_tab);
	else
		(*set)->cmd_nb = 0;
	(*set)->paths = ft_split(path, ':');
	free (path);
	(*set)->env_lst = envb;
	(*set)->envp = env_to_tab(envb);
	(*set)->cmd_set = cmd_struct_tab;
	(*set)->pid = NULL;
	return (*set);
}

char	**env_to_tab(t_env *lst)
{
	int		i;
	int		len;
	char	**tab;
>>>>>>> main

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


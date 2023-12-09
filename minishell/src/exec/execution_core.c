/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:40:11 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/09 17:36:19 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// first --> parsing1
// get the input and figures out the structure of cmds
// is builtin? --> run_builtin

// *************************

// preparation de l'execution -->
// recuperer a la strucutre initiee, (t_cmd **cmd_struct_tab)
//Pas de commande : cmd null --> parsing
// checker si  cmd_struct_tab[index][0] == 0 ou NULL)
//     si oui ---> penser a free / quiter ...
// checker en chaque cmd_struct_tab[index][0] si (is_builtins() == 1)  ?
//    si oui ---> charger les fonctions des builtins
// checker en chaque cmd_struct_tab[index][0] si on a une cmd executable
// si oui,
//  en fonction du nbr de cmd
//    pour N cmd --> initialiser (N - 1) pipes (communication entre process)
//    initier les fd_opens , les pipes , les here_docs ?
//    (tous elements utiles pour le fork() )
//
// execution
// Pour executer la cmd --> verifier si sa path  est complete ou non
//    si paht relative / absolute
// --> if (cmd->cmd && ft_strchr(cmd->cmd, '/'))
//execve(cmd->cmd, cmd->arg, data->env_copy);
//      else --> passer par get_cmd/path
// path => path = get_path(cmd->cmd, data);
/*
            if (path)
            {
              execve(path, cmd->arg, data->env_copy);
              free(path);
            }
          
          */
//

/*
  if cmd valid 
  while (cmd[0] et pas signal)
  {
    // regarder si on a un pipe 
      -- > pour lancer l'initialisation/processing du pipe, fork() , pid (pipex)
    // verifier si c'est pas une redirection suivi d'une mot
        (ou inversement a verifier ?)
      ---> avancer

    // verifier d'abord si c'est un builtin
      --> executer builtin // do_builtin
    // sinon si c'est une cmd
    // recuperer le path
    // executer + fork() 
     
  }
*/

// *****************************************


/*
int	is_builtin(char **command)
{
	if (ft_strncmp(command[0], "exit", 5))
		return (-1);
	else if (ft_strncmp(command[0], "echo", 5))
		return (1);
	else if (ft_strncmp(command[0], "cd", 3))
		return (1);
	else if (ft_strncmp(command[0], "pwd", 4))
		return (1);
	else if (ft_strncmp(command[0], "export", 7))
		return (1);
	else if (ft_strncmp(command[0], "unset", 6))
		return (1);
	else if (ft_strncmp(command[0], "env", 4))
		return (1);
	return (0);
}

void	ft_waitpid(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->cmds_nb && data->pid[i])
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
}

int	run_execution(t_data *data, t_cmd **cmd_struct_tab)
{
	int		index;
	char	**envp;

	printf("=======================run execution()===================\n");
	index = 0;
  pid_alloc(data);
	// if (data->lst_cmd == NULL || data->cmds_nb == 0)
	if (!data->lst_cmd || data->lst_cmd[index]->cmd == NULL)
	{
		free_cmd_struct_tab(cmd_struct_tab);
		return (0);
	}

	data->pipes = init_pipes(data);
	// cmd_struct_tab[i]->cmd[0]
	if (!(data->lst_cmd[index]->fd_in != 0 ||
			data->lst_cmd[index]->fd_out != 1) ||
		&data->lst_cmd[index]->cmd[1])
	{
		if (is_builtin(&data->lst_cmd[index]->cmd[0]) == 1)
			do_builtins(&data->lst_cmd[index]->cmd[0], &data->lst_env);
	}
	else
	{
		index = -1;
		envp = data->env_arr;
		// if (data->lst_cmd && data->lst_cmd[0] != (void *)'\0')
		//data->pipes = init_pipes(data);
		while (++index < data->cmds_nb)
		{
			if (pipe(data->fd) == -1)
				return (write(2, "pipe failed\n", 13), 0);
			//signal
			data->pid[index] = ft_fork(data, index);
		}
		ft_waitpid(data);
	}
	//free
	return (1);
}
*/
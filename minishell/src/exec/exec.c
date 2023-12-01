/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:42:21 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/01 17:03:15 by zaquedev         ###   ########.fr       */
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


/*
//void    ft_init_data(t_data *data, char **envp)
void    ft_init_data(t_data *data, t_env *lst_env)
{

  //char			*get_env_value(t_env *envb, char **str);
 //t_env			*get_env_node(t_env *lst, char *str);

 *data = (t_data){0, 0, 0, 0, 0, 0,0 ,0};

 data->lst_env = get_env(&lst_env->var_str);
 print_env(&data->lst_env);
 data->cmd_path = ft_read_path(data);   // data->paths = a faire ;
 printf("data->cmd_path = %s\n", data->cmd_path);
//data->cmds = a faire;
// px->cmd = get_cmd(px, px->cmd_paths, px->cmd_args[0], env); pipex
// px->cmd_paths = ft_split(px->paths, ':');
data->paths = set_tab_paths(data);
//printf("data->paths = %s\n", data->paths);
data->lexer= ft_lexer(data->cmd_line); // t_lexer	*ft_lexer(char *line)
data->lst_cmd = command_builder(&data->lexer);
data->cmds_nb = ft_nb_cmd(data->lexer->word); // cmd + builtins


}
*/


// void ft_isbuiltin(t_data *data, int index)
// {
  


// }
//void	ft_execution(t_data *data, char **envp)
// void	ft_execution(t_data *data, t_env *lst_env)
// {

//   // init data , cmd ...

//   // int	ft_fill_lexer(t_lexer **lexer_lst, char *cmd_line)

//  // ft_init_data(data, lst_env);
  
//   printf("data->cmd_path = %s\n", data->cmd_path);





// }

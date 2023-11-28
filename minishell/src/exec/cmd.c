/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:54:18 by zaquedev          #+#    #+#             */
/*   Updated: 2023/11/28 20:55:34 by zaquedev         ###   ########.fr       */
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
 data->cmd_path = ft_read_path(data);   // data->paths = a faire ;
 printf("data->cmd_path = %s\n", data->cmd_path);
//data->cmds = a faire;
// px->cmd = get_cmd(px, px->cmd_paths, px->cmd_args[0], env); pipex
// px->cmd_paths = ft_split(px->paths, ':');
data->paths = set_tab_paths(data);
//printf("data->paths = %s\n", data->paths);
//data->lexer= ft_lexer(data->cmd_line); // t_lexer	*ft_lexer(char *line)
//data->lst_cmd = command_builder(&data->lexer);
//data->cmds_nb = ft_nb_cmd(data->lexer->word); // cmd + builtins

}
*/

// void ft_isbuiltin(t_data *data, int index)
// {
  


// }
//void	ft_execution(t_data *data, char **envp)



void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void ft_path_ok_cmd(t_data *data, char **cmd, char **envp, int index)
{
    
    printf(" *********** ft_path_ok_cmd **********\n");
    char *cmd_find;

    cmd_find = set_path_cmd(data, cmd[0]);
    if(!cmd_find)
    {
      //free , exit ?
    
     // ft_free_tab((void **)envp);
     printf(" cmd_path //  = %s\n", data->lst_cmd[index]->cmd[0]);
     ft_free_char_tab(envp);
    }
}


char    **env_to_tab(t_env *lst)
{
    
    printf("\n==========Ici dans la fonction ---> env_to_tab==========\n");
    int        i;
    int        len;
    char        **tab;

    i = 0;
    len = ft_lstsize((t_list *)lst);
    printf("len = %d\n", len);
   // tab = (char **)malloc(sizeof(char *) * (len + 1));
     //tab = (char **)malloc(sizeof(char *) * (4096)); // 64 *

   
   // tab = ft_calloc(len + 1, sizeof(char *));
    tab = (char **)malloc((len + 1) * sizeof(char *));
    if (!tab)
    {
      printf("Unable to allocate memory.\n");
      exit(1);
       // return (NULL);
    }
      
    tab[len] = NULL;
    while (lst != NULL)
    {
        tab[i] = ft_strdup(lst->var_str);
        // if (!tab[i])
        //     return (ft_free_tab((void **)tab), NULL);
        lst = lst->next;
        i ++;
    }
    tab[i] = NULL;
    return (tab);    
}


/*
void	ft_print_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab !=NULL && *tab)
		{
			printf("tab[%d] = %s\n", i, (char *)tab[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("(NULL)\n");
}
*/

void	ft_print_char_tab(char **tab)
{
  
  int i;
  int j;
  
  if (tab == NULL) {
        printf("Tableau vide.\n");
        return;
  }
  
  i = 0;
 
  while (tab[i] != NULL)
  {
    j = 0;
    while (tab[i][j] != '\0')
    {
      printf("%c",tab[i][j]);
			j++;
    }
    printf("\n");
    i++;
  }



}






#include "../includes/minishell.h"



// typedef struct t_set
// {
//     char            **paths;
//     int                cmd_nb;
//     struct s_env    *envb; // would give access to envb if needed
//     struct s_cmd    **cmd_set; // would give access to cmd_struct_tab if needed
// }    t_set;






t_data   *init_set(t_data **data, t_cmd **cmd_struct_tab, t_env *envb)
{
   // t_env    *p;
    char    *path;
    //char *path_to_check;
    //path = ft_get_path(envb);
    
    // p = get_env_node(envb, "PATH");
    // if (!p || !p->var_str)
    //     return (NULL);
    // path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
    // if (!path)
    //     return (NULL);

    printf("*********** INIT_SET **************\n");


     printf("\n\n=======================PATH==========================\n");
    printf("\n1-PATH : --------------> \n");
     //  char *path ---> PATH = ....

    path = ft_get_path(envb); // la liste des chemins tous confondus : char * 

   
    *data = malloc(sizeof(t_data));
    if (!(*data))
        return (free (path), NULL);

    ft_memset(*data, 0, sizeof(t_data));
    (*data)->cmds_nb = ft_tab_len((char **)cmd_struct_tab);
    

     printf("\n2-cmds_nb : ---------------> \n");

     printf("(*data)->cmds_nb = %d\n", (*data)->cmds_nb);
   

    //******************************************************** 

    // char **paths --> data->paths  // tableau de listes de chemin : char **   
   
    printf("\n3-PATH[i] : ----------------->\n");
    if (path)
    {
        (*data)->paths = ft_split(path, ':');
        if (!(*data)->paths)
            printf("ERR_SPLIT\n"); // free

    }

    int count = ft_tab_len((char **)(*data)->paths);
    printf("count = %d\n", count);
    int i = 0;
    while (i < count)
    {
        printf("data->pahts[%i] = %s\n", i, (*data)->paths[i]);
        i++;
    }
    if (!(*data)->paths)
    {
        //return (printf("ERR_SPLIT\n"), NULL); // free!!!
        //free((*data)->paths);
        free (path);
    }
    free (path);
  
    printf("\n\n=======================ENVB==========================\n");

    printf("\n4-ENVB[i] : **************\n");

    (*data)->lst_env = envb;
    printf("\n\nenvb = \n");
    t_env *tmpenv = envb;
    
    while (tmpenv)
    {
        printf("tmpenv->var_str[] = %s\n ", tmpenv->var_str);
        tmpenv = tmpenv->next;
    }

     printf("\n\n=======================char *ENVB[i]==========================\n");

     printf("\n5- char *ENVB[i] :   char **tabenv ??? \n");
    //char **tabenv;

    

     printf("\n\n======================= tabenv = env_to_tab(envb)==========================\n");

    // tabenv = env_to_tab(envb);
    // printf("envp \n ft_print_char_tab = \n");
    // ft_print_char_tab(tabenv);




    (*data)->lst_cmd = cmd_struct_tab;

    // cmd ?? <--- cmd_struct_tab[index][0]
     // (*data)->cmd_path = set_path_cmd(*data, cmd_struct_tab[0]->cmd[0]);
   
    return (*data);
} 



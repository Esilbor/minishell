


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

    printf("*********** init_set **************\n");

    path = ft_get_path(envb); // la liste des chemins tous confondus : char * 

    // if (path)
    // {
    //     (*data)->paths = ft_split(path, ':');
    //     if (!(*data)->paths)
    //         printf("ERR_SPLIT\n"); // free

    // }
    *data = malloc(sizeof(t_data));
    if (!(*data))
        return (free (path), NULL);

    ft_memset(*data, 0, sizeof(t_data));
    (*data)->cmds_nb = ft_tab_len((char **)cmd_struct_tab);
     printf("(*data)->cmds_nb = %d\n", (*data)->cmds_nb);
    (*data)->paths = ft_split(path, ':'); // tableau de listes de chemin : char **   
    //if (!(*data)->paths)
	// 		printf("ERR_SPLIT\n");

    int count = ft_tab_len((char **)(*data)->paths);
    printf("count = %d\n", count);
    int i = 0;
    while (i < count)
    {
        printf("data->pahts[%i] = %s\n", i, (*data)->paths[i]);
        i++;
    }

    // printf("data->pahts[0] = %s\n", (*data)->paths[0]);
    // printf("data->pahts[1] = %s\n", (*data)->paths[1]);


    if (!(*data)->paths)
    {
        //return (printf("ERR_SPLIT\n"), NULL); // free!!!
        //free((*data)->paths);
        free (path);
    }
    free (path);
    (*data)->cmd_path = set_path_cmd(*data, cmd_struct_tab[0]->cmd[0]);
   

    (*data)->lst_env = envb;
    (*data)->lst_cmd = cmd_struct_tab;

   
    return (*data);
} 
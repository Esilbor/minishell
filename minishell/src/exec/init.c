


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

    path = ft_get_path(envb);
    
    // p = get_env_node(envb, "PATH");
    // if (!p || !p->var_str)
    //     return (NULL);
    // path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
    // if (!path)
    //     return (NULL);

    *data = malloc(sizeof(t_data));
    if (!(*data))
        return (free (path), NULL);
    ft_memset(*data, 0, sizeof(t_data));
    (*data)->cmds_nb = ft_tab_len((char **)cmd_struct_tab);
    (*data)->paths = ft_split(path, ':');
    if (!(*data)->paths)
    {
        //return (printf("ERR_SPLIT\n"), NULL); // free!!!
        //free((*data)->paths);
        free (path);
    }
    free (path);
    (*data)->lst_env = envb;
    (*data)->lst_cmd = cmd_struct_tab;
    // ft_print_tab((void **)(*set)->paths, "envb");
    // ft_print_struct_tab((*set)->cmd_set);
    return (*data);
} 
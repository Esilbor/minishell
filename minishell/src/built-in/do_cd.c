#include "../../includes/minishell.h"

int     do_cd(char **str, t_env **envb)
{
    char   *tmp;

    tmp = getcwd(NULL, 0);
    if (str[1] == NULL)
    {
        chdir((const char *)get_env_node(*envb, "HOME"));
        free(tmp);
        return (1);
    }
    else if (str[1][0] == '~')
    {
        chdir((const char *)get_env_node(*envb, "HOME"));
        free(tmp);
        return (1);
    }
    else if (chdir(str[1]) == -1)
    {
        ft_printf("minishell: cd: %s: %s\n", str[1], strerror(errno));
        free(tmp);
        return (0);
    }
    free(tmp);
    return (1);
}
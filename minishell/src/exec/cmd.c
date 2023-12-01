/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:54:18 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/01 17:04:52 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_path_ok_cmd(t_data *data, char **cmd, char **envp, int index)
{
	char	*cmd_find;

	printf(" *********** ft_path_ok_cmd **********\n");
	cmd_find = set_path_cmd(data, cmd[0]);
	if (!cmd_find)
	{
		//free , exit ?
		// ft_free_tab((void **)envp);
		printf(" cmd_path //  = %s\n", data->lst_cmd[index]->cmd[0]);
		ft_free_char_tab(envp);
	}
}

char	**env_to_tab(t_env *lst)
{
	int		i;
	int		len;
	char	**tab;

	printf("\n==========Ici dans la fonction ---> env_to_tab==========\n");
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
		i++;
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
	int	i;
	int	j;

	if (tab == NULL)
	{
		printf("Tableau vide.\n");
		return ;
	}
	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			printf("%c", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

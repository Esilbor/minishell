/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:54:18 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/02 19:27:24 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_char_tab(char **tab)
=======
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/06 13:12:45 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	string_empty(char *str)
>>>>>>> main
{
	int	i;

	i = 0;
<<<<<<< HEAD
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
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
=======
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}

static char	*check_cmd_null(char *cmd)
{
	if (!cmd || string_empty(cmd))
	{
		//write(STDERR, ERR_CMD, ft_strlen(ERR_CMD));
		//return (NULL);
		return (ft_putstr_fd("ERR_CMD\n", 2), NULL);
	}
	return (cmd);
}

char *set_path_cmd(t_set *set, char *cmd)
{
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (ft_putstr_fd("ERR_MALLOC\n", 2), NULL); // free!!!

	while (set->paths[index])
	{
		cmd_tmp = ft_strjoin(set->paths[index], tmp);
		if (!cmd_tmp)
		{
			free(tmp);
			return (ft_putstr_fd("ERR_MALLOC\n", 2), NULL); // free!!!
		}

		if (access(cmd_tmp, X_OK | F_OK) == 0)
			return (cmd_tmp);
		free (cmd_tmp);
		index++;
	}
	ft_putstr_fd("\ncmd_path not found\n", 2);
	return (NULL);
>>>>>>> main
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:45:47 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 21:22:30 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


char	**assign_paths(t_set **set, t_env *envb)
{
	char	*path;
	t_env	*p;

	p = get_env_node(envb, "PATH");
	if (!p || !p->var_str)
		return (NULL);
	path = ft_strdup(ft_strchr(p->var_str, '=') + 1);
	if (!path)
		return (NULL);
	(*set)->paths = ft_split(path, ':');
	if (!(*set)->paths)
		return (NULL);
	free (path);
	return ((*set)->paths);
}

t_set	*init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb)
{
	*set = malloc(sizeof(t_set));
	if (!(*set))
		return (/* free (path),  */NULL);
	ft_memset(*set, 0, sizeof(t_set));
	if (cmd_struct_tab && cmd_struct_tab[0])
		(*set)->cmd_nb = ft_tab_len((char **)cmd_struct_tab);
	else
		(*set)->cmd_nb = 0;
	(*set)->env_lst = envb;
	assign_paths(set, envb);
	(*set)->envp = env_to_tab(envb);
	(*set)->cmd_set = cmd_struct_tab;
	//(*set)->pid = NULL;
	(*set)->pid = 0;
	//g_exit_val = 0;
	update_ret(&(*set)->env_lst, g_exit_val);
	return (*set);
}

char	**env_to_tab(t_env *lst)
{
	int		i;
	int		len;
	char	**tab;

	i = 0;
	len = ft_lstsize((t_list *)lst);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = NULL;
	while (lst)
	{
		tab[i] = ft_strdup(lst->var_str);
		if (!tab[i])
			return (ft_free_tab((void **)tab), NULL);
		lst = lst->next;
		i ++;
	}
	return (tab);
}

void	sugar_rush(t_set *set)
{
	free(set->pipe[0]);
	free(set->pipe[1]);
	free(set->pipe);
	ft_free_tab((void **) set->paths);
	ft_free_tab((void **) set->envp);
	free_redirections(set->cmd_set);
	free_cmds((t_cmd **)set->cmd_set);
	free(set);
}

// void	init_pid_tab(t_set *set)
// {
// 	int	i;

// 	i = -1;
// 	set->pid = malloc(sizeof (pid_t) * set->cmd_nb);
// 	if (!set->pid)
// 		return (ft_putstr_fd("could not malloc pid_tab", 2));
// 	while (++i < set->cmd_nb)
// 		set->pid[i] = 0;
// }

void	execution(t_set *set, t_cmd **cmd_struct_tab, t_env *envb)
{
	init_set(&set, cmd_struct_tab, envb);
	init_pipe_set(set);
	ft_pipex(set);
	sugar_rush(set);
}
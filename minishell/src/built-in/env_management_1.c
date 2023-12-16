/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:51:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/16 19:39:47 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//env -i bash
//env
//>> il ne reste que PWD= et SHLVL=
// ne pas gerer _=

//ne pas utiliser ft_printf
// utiliser write (avec une protection)
// error message handling

#include "../../includes/minishell.h"

// Functions primarily dealing with environment variables 

void	ft_free_env_lst(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var_str);
		free(tmp);
	}
}

t_env	*ft_last_env_node(t_env *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

void	ft_add_env_node(t_env **env, char *varp)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	new_node->var_str = ft_strdup(varp);
	if (!new_node->var_str)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
		ft_last_env_node(*env)->next = new_node;
}

// duplicate and return a t_env chained list
t_env	**dup_env(t_env **env)
{
	t_env	**dup;
	t_env	*lst;

	lst = *env;
	dup = malloc(sizeof(t_env *));
	if (!dup)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	*dup = NULL;
	while (lst)
	{
		ft_add_env_node(dup, lst->var_str);
		lst = lst->next;
	}
	return (dup);
}

void	ft_fill_env(t_env **env, char **envp)
{
	int		i;
	t_env	*lst;

	i = -1;
	lst = *env;
	ft_add_env_node(&lst, "?=0");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "_=", 2))
			continue ;
		ft_add_env_node(&lst, envp[i]);
	}
	*env = lst;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handling_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:27:54 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/21 10:37:30 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Functions focused on export command

void	create_var(char **v_tab, char **cmd_tab, t_env **env, int i)
{
	char	*tmp;
	char	*tmp2;

	if (assign_or_append(cmd_tab[i]) == 1)
	{
		tmp = ft_strjoin(v_tab[0], "=");
		tmp2 = ft_strjoin(tmp, v_tab[1]);
		ft_add_env_node(env, tmp2);
		free(tmp);
		free(tmp2);
	}
	else if (assign_or_append(cmd_tab[i]) == 0)
	{
		ft_add_env_node(env, cmd_tab[i]);
	}
}

// variable already exists and is assigned a new value
// variable already exists and appends a value
void	modify_var(t_env *node, char **v_tab, char **cmd_tab, int i)
{
	char	*tmp;

	if (node && assign_or_append(cmd_tab[i]) == 0)
	{
		free(node->var_str);
		node->var_str = ft_strdup(cmd_tab[i]);
	}
	else if (node && assign_or_append(cmd_tab[i]) == 1)
	{
		tmp = ft_strdup(node->var_str);
		free(node->var_str);
		node->var_str = ft_strjoin(tmp, v_tab[1]);
		free(tmp);
	}
}

int	update_ret(t_env **env, int ret)
{
	t_env	*node;
	char	*str_ret;

	str_ret = ft_itoa(ret);
	node = get_env_node(*env, "?");
	if (!node)
		return (ft_putstr_fd("could not update ret\n", 2), -1);
	free (node->var_str);
	node->var_str = ft_strjoin("?=", str_ret);
	free(str_ret);
	return (ret);
}

int	do_export(int cmd_nb, char **cmd_tab, t_env **env)
{
	int		i;
	t_env	*node;
	char	**value_tab;
	int		ret;

	i = 1;
	ret = 0;
	while (i < cmd_nb)
	{
		if (cmd_is_valid(cmd_tab, i, &ret) && assign_or_append(cmd_tab[i]) >= 0)
		{
			value_tab = ft_split_value(cmd_tab[i]);
			node = get_env_node(*env, value_tab[0]);
			if (node)
				modify_var(node, value_tab, cmd_tab, i);
			else if (!node)
				create_var(value_tab, cmd_tab, env, i);
			ft_free_tab((void **)value_tab);
		}
		i++;
	}
	return (update_ret(env, ret));
}

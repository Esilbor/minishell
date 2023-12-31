/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handling_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:27:54 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/31 15:52:49 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
int	modify_var(t_env *node, char **v_tab, char **cmd_tab, int i)
{
	char	*tmp;

	if (node && assign_or_append(cmd_tab[i]) == 0)
	{
		free(node->var_str);
		node->var_str = ft_strdup(cmd_tab[i]);
		if (!node->var_str)
			return (-1);
	}
	else if (node && assign_or_append(cmd_tab[i]) == 1)
	{
		tmp = ft_strdup(node->var_str);
		if (!tmp)
			return (-1);
		free(node->var_str);
		node->var_str = ft_strjoin(tmp, v_tab[1]);
		free(tmp);
	}
	return (0);
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

static int	process_command(char **cmd_tab, int i, t_env **env)
{
	char	**value_tab;
	t_env	*node;

	value_tab = ft_split_value(cmd_tab[i]);
	if (!value_tab)
		return (-1);
	node = get_env_node(*env, value_tab[0]);
	if (node)
	{
		if (modify_var(node, value_tab, cmd_tab, i) < 0)
		{
			ft_free_tab((void **)value_tab);
			return (-1);
		}
	}
	else
		create_var(value_tab, cmd_tab, env, i);
	ft_free_tab((void **)value_tab);
	return (0);
}

int	do_export(int cmd_nb, char **cmd_tab, t_env **env)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (i < cmd_nb)
	{
		if (cmd_is_valid(cmd_tab, i, &ret) && assign_or_append(cmd_tab[i]) >= 0)
		{
			if (process_command(cmd_tab, i, env) < 0)
				return (-1);
		}
		i++;
	}
	return (update_ret(env, ret));
}

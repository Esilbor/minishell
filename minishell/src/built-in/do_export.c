/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:27:54 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/10 16:21:03 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//return the env_node matching the str or NULL if no match
t_env	*get_env_node(t_env *lst, char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	while (lst)
	{
		if (!ft_strncmp(lst->var_str, str, ft_strlen(str))
			&& lst->var_str[str_len] == '=')
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

// return 0 for assign, 1 for append or -1 if no equal sign
int	assign_or_append(char *env_var)
{
	char	*equal;
	char	*plus;

	equal = ft_strchr(env_var, '=');
	if (!equal)
		return (-1);
	plus = ft_strchr(env_var, '+');
	if (plus && *(plus + 1) == '=')
		return (1);
	return (0);
}

// split the input line for export according to '=' or "+="
char	**ft_split_value(char *var)
{
	char	*equal;
	char	*plus;
	char	*tmp;
	char	**ret_tab;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		ret_tab = malloc(sizeof(char *) * 2);
		ret_tab[0] = ft_strdup(var);
		ret_tab[1] = NULL;
		return (ret_tab);
	}
	plus = ft_strchr(var, '+');
	if (plus && *(plus + 1) == '=')
	{
		ret_tab = ft_split(var, '+');
		tmp = ret_tab[1];
		free(ret_tab[1]);
		ret_tab[1] = ft_strdup(equal + 1);
	}
	if (equal && !plus)
		ret_tab = ft_split(var, '=');
	return (ret_tab);
}

void	print_err(char *invalid_cmd, char *cmd_name)
{
	ft_putstr_fd("Candy_$hell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(":'", 2);
	ft_putstr_fd(invalid_cmd, 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
}

// return true if cmd is valid or syntaxe err msg
bool	cmd_is_valid(char **cmd_tab, int i, int *ret)
{
	int	j;

	j = 0;
	if (ft_isdigit((int)cmd_tab[i][0]))
	{
		*ret = 1;
		return (print_err(cmd_tab[i], cmd_tab[0]), false);
	}
	while (cmd_tab[i][j])
	{
		if (!ft_strcmp(cmd_tab[0], "export")
			&& ((ft_isalnum((int)cmd_tab[i][j]) || cmd_tab[i][j] == '_'
			|| cmd_tab[i][j] == '=' || cmd_tab[i][j] == '+')))
				j++;
		else if (!ft_strcmp(cmd_tab[0], "unset")
			&& (ft_isalnum((int)cmd_tab[i][j]) || cmd_tab[i][j] == '_'))
				j++;
		else
		{
			*ret = 1;
			return (print_err(cmd_tab[i], cmd_tab[0]), false);
		}
	}
	return (true);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:23:53 by esilbor           #+#    #+#             */
/*   Updated: 2023/11/21 14:22:55 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Functions for displaying environment settings

int	ft_print_rainbow(char *str)
{
	int				i;
	unsigned int	color_index;
	int				num_colors;
	char			*colors[8];

	init_colors(colors);
	num_colors = sizeof(colors) / sizeof(colors[0]);
	color_index = ft_rand() % num_colors;
	i = -1;
	while (str[++i])
	{
		if (write(1, colors[color_index], ft_strlen(colors[color_index]))
			!= ft_strlen3(colors[color_index]))
			return (ft_putstr_fd(strerror(errno), 2), -1);
		if (write(1, &str[i], 1) != 1)
			return (ft_putstr_fd(strerror(errno), 2), -1);
	}
	write(1, "\033[0m", 4);
	write(1, "\n", 1);
	return (0);
}

void	print_env(t_env **head)
{
	t_env	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->var_str)
			ft_print_rainbow(lst->var_str);
		else
			ft_printf("(null)\n");
		lst = lst->next;
	}
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

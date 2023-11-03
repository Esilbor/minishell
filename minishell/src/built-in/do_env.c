/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:51:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/02 14:47:41 by bbresil          ###   ########.fr       */
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
	new_node->var_str = ft_strdup(varp); //ft_strdup can fail and return NULL
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
		return ( NULL);
	}
	*dup = NULL;
	while (lst)
	{
		ft_add_env_node(dup, lst->var_str);
		lst =lst->next;
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

unsigned int	ft_rand(void)
{
	static unsigned int	seed = 123456789;
	const unsigned int	a = 48271;
	const unsigned int	m = 2147483647;

	seed = (a * seed) % m;
	return (seed);
}

void	init_colors(char **colors)
{
	colors[0] = PINK;
	colors[1] = GREEN;
	colors[2] = BLUE;
	colors[3] = PURPLE;
	colors[4] = CYAN;
	colors[5] = YELLOW;
	colors[6] = PINK;
	colors[7] = YELLOW;
}

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

// t_env	**dup_env(t_env **head)
// {
// 	t_env
// }

t_env	**sort_env(t_env **head)
{
	int		swapped;
	t_env	*current;
	t_env	*prev;
	t_env	*next_node;
	char	*tmp;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return (head);
	swapped = 1;
	while (swapped)
	{
		current = *head;
		prev = NULL;
		swapped = 0;
		while (current != NULL && current->next != NULL)
		{
			next_node = current->next;
			if (ft_strcmp(current->var_str, next_node->var_str) > 0)
			{
				tmp = current->var_str;
				current->var_str = next_node->var_str;
				next_node->var_str = tmp;
				swapped = 1;
				if (prev == NULL)
					*head = current;
			}
			prev = current;
			current = next_node;
		}
	}
	return (head);
}

void	print_env(t_env **head)
{
	t_env	*lst;
	int		col;

	col = 0;
	lst = *head;
	while (lst)
	{
		// lst = lst->next; // skip ?= used for $?
		if (lst->var_str)
			ft_print_rainbow(lst->var_str);
		else
			ft_printf("(null)\n");
		lst = lst->next;
	}
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	env = NULL;
	ft_fill_env(&env, envp);
	return (env);
}

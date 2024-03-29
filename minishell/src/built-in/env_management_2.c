/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:51:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/14 07:07:08 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	swap_env_nodes(t_env **head)
{
	int		swapped;
	t_env	*current;
	t_env	*prev;
	t_env	*next_node;
	char	*tmp;

	current = *head;
	prev = NULL;
	swapped = 0;
	while (current && current->next)
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
	return (swapped);
}

t_env	**sort_env(t_env **head)
{
	int	i;

	i = 0;
	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return (head);
	while (swap_env_nodes(head))
		i++;
	return (head);
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	env = NULL;
	ft_fill_env(&env, envp);
	return (env);
}

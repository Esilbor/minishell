/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:55 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/07 10:44:09 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//change the color display of the prompt according to $?
char	*ft_prompt(t_env *envb)
{
	char	*input;
	t_env	*ret_node;

	ret_node = get_env_node(envb, "?");
	if (!ft_strncmp(ret_node->var_str, "?=0", 4))
		input = readline(PROMPT);
	else if (!ft_strncmp(ret_node->var_str, "?=1", 4))
		input = readline(PROMPT1);
	else if (!ft_strncmp(ret_node->var_str, "?=2", 4))
		input = readline(PROMPT2);
	else
		input = readline(PROMPT3);
	return (input);
}

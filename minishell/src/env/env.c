/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:55 by bbresil           #+#    #+#             */
/*   Updated: 2024/01/02 18:42:22 by zaquedev         ###   ########.fr       */
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
	if (g_exit_val == 130)
		update_ret(&envb, g_exit_val);
	return (input);
}

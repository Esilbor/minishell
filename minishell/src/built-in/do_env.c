/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:12:45 by zaquedev          #+#    #+#             */
/*   Updated: 2024/01/02 16:51:01 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	env_is_valid(t_set *set, int index)
{
	int	i;

	i = 0;
	while (set->cmd_set[index]->cmd[i]
		&& !ft_strncmp(set->cmd_set[index]->cmd[i], "env", 4))
		i++;
	if (ft_tab_len(set->cmd_set[index]->cmd) == i)
		return (true);
	if (set->cmd_set[index]->cmd[1])
		invalid_input(set->cmd_set[index]->cmd[i]);
	return (false);
}

int	do_env(t_set *set, t_env *env, int index)
{
	if (env_is_valid(set, index))
	{
		if (print_env(set, &env) < 0)
			return (update_ret(&env, -1));
		return (update_ret(&env, 0)); // g_exit_val = 0; ?
	}
	return (update_ret(&env, 127));
}
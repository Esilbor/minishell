/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:37:15 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/26 16:35:49 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// closes pipe file descriptors if exist
void	ft_close_pipes(t_set *set)
{
	if (set->pipe[0][0])
		close(set->pipe[0][0]);
	if (set->pipe[0][1])
		close(set->pipe[0][1]);
	if (set->pipe[1][0])
		close(set->pipe[1][0]);
	if (set->pipe[1][1])
		close(set->pipe[1][1]);
}
void	close_pipe(t_set *set, int index)
{
	close(set->pipe[(index + 1) % 2][0]);
	close(set->pipe[(index + 1) % 2][1]);
}

void	init_pipe_set(t_set *set)
{
	set->pipe = malloc(sizeof(int *) * 2);
	if (!set->pipe)
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe set", 2));
	set->pipe[0] = malloc(sizeof (int) * 2);
	if (!set->pipe[0])
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe[0]", 2));
	set->pipe[1] = malloc(sizeof (int) * 2);
	if (!set->pipe[1])
	{
		free (set->pipe[0]);
		return (free (set->pipe), ft_putstr_fd("could not malloc pipe[1]", 2));
	}
	set->pipe[0][0] = 0;
	set->pipe[0][1] = 0;
	set->pipe[1][0] = 0;
	set->pipe[1][1] = 0;
}

void	ft_error(char *message, t_set *set)
{
	write(2, message, ft_strlen(message));
	free_after_builtin(set);
	ft_close_pipes(set);
	exit(1);
}

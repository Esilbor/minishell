/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:43:05 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 17:43:22 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// closes the standard input (STDIN_FILENO)
// and sets a global variable g_exit_val to 130
void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_exit_val = 130;
	}
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}

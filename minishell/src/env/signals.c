/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:10 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/14 21:14:28 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



// Handle SIGINT signal and print a prompt  
// on affiche le promp
// cursur au debut de la ligne
// remplacer la ligne actuelle par une chaine vide
// redisplay pour mettre a jour l'affichage

// mode interactif ? 
// ctrl_c ==> SIGINT

int g_exit_val;

void	sigint_handler(int signum) 
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay(); 
		//g_exit_val = 130;
	}
}

/*
*	Fonction principale : general / parent / main
*	initialisation des signaux :
*	sigint_handler -- > (ctrl-c) 
*	ign_sigquit --- > (ctrl-\) replaced with SIG_IGN
*/

void	ft_handle_signals(void)
{
	struct sigaction	sa; 
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sigint_handler; 
	sigaction(SIGINT, &sa, NULL);	
	ign_sigquit();
	
}



/* 
*	SIGQUIT signals (ctrl-\) replaced with SIG_IGN
*/
void	ign_sigquit(void) 
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	//ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

/* 
*	SIGINT signals (ctrl-c) replaced with SIG_IGN
*/

void	ign_sigint(void) 
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

// fonction par defaut:

void signals_simple(void)
{
	struct sigaction	sa; 

	ft_memset(&sa, 0, sizeof(sa)); 
	sa.sa_handler = SIG_DFL; // if child_pid == 0
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}
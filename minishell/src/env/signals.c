/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:10 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/12 20:21:50 by zaquedev         ###   ########.fr       */
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

void	sigint_handler(int signum) 
{
	(void)signum; // Avoid compiler warning for unused variable
	if (signum == SIGINT)
	{
		//ft_printf("\001"PINK"\002""\nCandy_Shell> ""\001"YELLOW"\002");
		//ft_printf("\001"PINK"\002""\n""\001"YELLOW"\002");
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//set->status = 130;
	}
}



void	sigquit_handler(int signum) // ctrl- D
{
	// if (signum == SIGQUIT) 
	// {
	// 	exit(131);
	// }
	(void)signum; // This handler does nothing for SIGQUIT
}



void	ft_handle_signals(void)
{
	struct sigaction	sa; // struct sigaction sa = {0}; declaration de la structure 
							// et initialisation a zero
		// Handling SIGINT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure
	sa.sa_handler = &sigint_handler; // Assign handler function // 
	sigaction(SIGINT, &sa, NULL); // Register handler for SIGINT
	
	// Handling SIGQUIT
	//ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure again
	sa.sa_handler = &sigquit_handler; // Assign handler function
	sigaction(SIGQUIT, &sa, NULL); // Register handler for SIGQUIT
}


/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
// ctrl-\
*/
void	ign_sigquit(void) 
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}




// void	slash(int sig)
// {
// 	if (sig == SIGQUIT)
// 		exit(131);
// 	if (sig == SIGINT)
// 		exit(130);
// }
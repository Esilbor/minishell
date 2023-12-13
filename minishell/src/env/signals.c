/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:10 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/13 20:18:00 by zaquedev         ###   ########.fr       */
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
	//ft_printf("\001"PINK"\002""\nCandy_Shell> ""\001"YELLOW"\002");
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_val = 130;
	}		
}

// ctrl-/

// void	sigquit_handler(int signum) 
// {
// 	(void)signum; 
// 	rl_on_new_line();
// 	g_exit_val = 131;
// }


/*
*	Fonction principale : child(pid == 0)
*	initialisation des signaux ctrl -c // ctrl \
*/
// void signals_ctrlc_bsl(void)
// {
// 	struct sigaction	sa; 
		 
// 	ft_memset(&sa, 0, sizeof(sa)); 
// 	sa.sa_handler = &sigquit_handler;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGINT, &sa, NULL);
// }

/*
*	Fonction principale : general / parent
*	initialisation des signaux
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
}

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
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}




// Handle SIGINT signal and print a prompt  
// on affiche le promp
// cursur au debut de la ligne
// remplacer la ligne actuelle par une chaine vide
// redisplay pour mettre a jour l'affichage

// mode interactif ? 
// ctrl_c ==> SIGINT

/*
void	sigint_handler(int signum) 
{
	//ft_printf("\001"PINK"\002""\nCandy_Shell> ""\001"YELLOW"\002");
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}		
}

// ctrl-/

void	sigquit_handler(int signum) 
{
	(void)signum; 
	rl_on_new_line();
}


*	Fonction principale : child(pid == 0)
*	initialisation des signaux ctrl -c // ctrl \

void signals_ctrlc_bsl(void)
{
	// Handling SIGQUIT
	struct sigaction	sa; 
		 
	ft_memset(&sa, 0, sizeof(sa)); 
	sa.sa_handler = &sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}


*	Fonction principale : general / parent
*	initialisation des signaux


void	ft_handle_signals(void)
{
	struct sigaction	sa; 
		// Handling SIGINT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure
	sa.sa_handler = &sigint_handler; // Assign handler function // 
	sigaction(SIGINT, &sa, NULL);
	
	// Handling SIGQUIT ---> SIG_IGN
	// ft_memset(&sa, 0, sizeof(sa)); 
	// sa.sa_handler = &sigquit_handler;
	// sigaction(SIGQUIT, &sa, NULL); 
	ign_sigquit();
}



//	SIGQUIT signals (ctrl-\) replaced with SIG_IGN

void	ign_sigquit(void) 
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

*/






















/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:10 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/09 20:46:28 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle SIGINT signal and print a prompt
void	sigint_handler(int signum)
{
	(void)signum; // Avoid compiler warning for unused variable
	ft_printf("\001"PINK"\002""\nCandy_Shell> ""\001"YELLOW"\002");
}

void	sigquit_handler(int signum)
{
	(void)signum; // This handler does nothing for SIGQUIT
}

void	ft_handle_signals(void)
{
	struct sigaction	sa;
		// Handling SIGINT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure
	sa.sa_handler = sigint_handler; // Assign handler function // 
	sigaction(SIGINT, &sa, NULL); // Register handler for SIGINT
	// Handling SIGQUIT
	ft_memset(&sa, 0, sizeof(sa)); // Zero out the structure again
	sa.sa_handler = sigquit_handler; // Assign handler function
	sigaction(SIGQUIT, &sa, NULL); // Register handler for SIGQUIT
}


/*
MANIPULATION DES SIGNAUX :

Lorsqu’un evenement exceptionnel se produit, le systeme d’exploitation peut
envoyer un signal aux processus.


Signal | significations :

SIGINT	: interuPtion par la touche Ctrl-C



Deux fonctions permettent d’interagir avec le m´ecanisme des signaux :
Fonct	| Prototype 							| Action
raise	: int raise(int sig)					: Envoie le signal sig au processus ex´ecutant.
signal 	:	typedef void (*sigh_t)(int);		: signum. handler est un pointeur vers la fonction effectuant le traitement de ce signaL
		:	sigh_t signal(int signum,
		:	sigh_t handler) ;







*/
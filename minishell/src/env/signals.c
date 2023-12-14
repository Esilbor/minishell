/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:10 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/14 16:20:06 by zaquedev         ###   ########.fr       */
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

	void	ctrl_c(int sig)
{
	(void)sig;
	if (!(data())->child_ids && (data())->temp_pid < 0 && !(data())->passif_mode)
	{
		(data())->exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
	else if ((data())->in_hrd)
	{
		write(1, "\n", 1);
		close((data())->temp_pipe[P_WR]);
		free_p_struct(&(data())->lines);
		exit(exit_properly(130));
	}
	else
	{
		write(1, "\n", 1);
		(data())->exit_code = 130;
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if ((data())->passif_mode)
	{
		(data())->exit_code = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

int	ft_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_bs);
	return (1);
}


*/


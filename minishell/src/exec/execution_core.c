/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:40:11 by zaquedev          #+#    #+#             */
/*   Updated: 2023/12/01 16:57:28 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

// first --> parsing1
// get the input and figures out the structure of cmds
// is builtin? --> run_builtin

// *************************

        // preparation de l'execution --> 
        // recuperer a la strucutre initiee, (t_cmd **cmd_struct_tab)
        // checker en chaque cmd_struct_tab[0] si (is_builtins() == 1)  ?
				// charger les fonctions des builtins 
				//    initier les fd_opens , les pipes , les here_docs ?
				//    (tous elements utiles pour le fork() )
				// 	execution
        
// *****************************************     

static int		is_builtin(char **command)
{
	if (ft_strncmp(command[0], "exit", 5))
		  return (-1);
	else if (ft_strncmp(command[0], "echo", 5))
		  return (1);
	else if (ft_strncmp(command[0], "cd", 3))
		  return (1);
 else if (ft_strncmp(command[0], "pwd", 4))
		  return (1);
   else if (ft_strncmp(command[0], "export", 7))
    return (1);
	else if (ft_strncmp(command[0], "unset", 6))
		return (1);
	else if (ft_strncmp(command[0], "env",4))
		return (1);
	return (0);
}


/*

  if cmd valid 
  while (cmd[0] et pas signal)
  {
    // regarder si on a un pipe 
      -- > pour lancer l'initialisation/processing du pipe, fork() , pid (pipex)
    // verifier si c'est pas une redirection suivi d'une mot
        (ou inversement a verifier ?)
      ---> avancer

    // verifier d'abord si c'est un builtin
      --> executer builtin // do_builtin
    // sinon si c'est une cmd
    // recuperer le path
    // executer + fork() 
     
  }






*/
  
void run_execution(t_data *data)
{
    int index;
    index = 0; 
    
    // if (is_redirction())
    // {

      
    // }
    // cmd_struct_tab[i]->cmd[0]
    if (is_builtin(&data->lst_cmd[index]->cmd[0]) == 1)
    {
      do_builtins(&data->lst_cmd[index]->cmd[0], &data->lst_env);
    }
      


  
}









/*

int single_cmd(t_data *data, t_cmd **lst_cmd);

int pipeline_cmd(t_data *data);



int exec_cmd(t_data *data)
{
  int res;

  if (data->cmds_nb == 1)
      res = single_cmd(data, data->lst_cmd[0]->cmd[0]);
  else
      res = pipeline_cmd(data);
  return (res);
}
*/



int ft_exexution(t_data *data)
{
  int res = 0;
  
  if (!data->cmds_nb)
		{
      //res = exec_cmd(data);        
		}
    return (res);  
}








// http://i.paysdu42.fr/?page=minishell.c




/*
  ETAPE 3 LANCER UN PROGRAMME - FORKER
  Une fois qu’on a recuperer le path, qu’on sait que c’est le bon, on va
  forker. Pourquoi ? parce qu’apres avoir lancer execve, le programme s’arrete.
  On veut arreter le programme, pas le minishell. Il faut donc duppliquer le
  prog. C’est le role de fork. Le cours explique comment il marche.
  A vous de jouer.
*/

/*
  ETAPE 3 LANCER UN PROGRAMME - EXECVE
  execve doit etre execute dans le fils. S’il reussit, alors il ne fera pas ce
  qu’il y a apres puisqu’il quitte. Sinon, il le fera.
  il prend en parametre le path calcule precedemment et un tableau a deux
  dimemsions vers chaque arguments exemple :
  {"ls", "-l", "-a", ".", NULL}
  ca tombe bien, c’est exectement ce qu’on a fait avec le str_to_wordtab.
  et l’environnement sous forme d’un tableau.
*/

/*
  et voila ! On a lance un programme a partir de notre minishell.
  Maintenant, on a quelques builtins a realiser. 
  env, setenv et unsetenv. Le mieux serait de le faire avec des listes
  chainees. Je vous ai appris a en faire dans un precedent cours.
  Si vous n’etes pas a l’aise, vous pouvez utiliser des tableaux.
*/

/*
  ETAPE 4 ENV
  -> Si vous prenez la solution liste chainee (trop classe wahou), faites une
     fonction qui transforme le char **env en t_list *env. Cette fonction
     ressemblera a l’exo de piscine "my_params_in_list.c" (Jour 11).
     Afficher cette liste.
  -> Si vous choisissez de garder un tableau, afficher simplement ce tableau.
*/

/*
  ETAPE 5 SETENV
  liste chainee : ajouter un element a la liste. A la fin de la liste. Pas
  tres difficile :) mais attention, vous devez verifier si l’element n’
  existe pas deja et si c’est le cas modifier cet element.
  tableau : ajouter un element a la fin du tableau. Pour ca, il va falloir
  faire un realloc, c’est a dire free(env) (sauf si c’est le tableau de depart)
  malloc(la taille du tableau d’avant + 1). pareil, si l’element existe,
  il faut le modifier.
*/

/*
  ETAPE 6 UNSETENV
  liste chainee : parcourir sa liste, trouver (ou pas) l’element, l’enlever.
  pop_elem_from_list (google :))
  tableau : parcourir le tableau, trouver (ou pas) l’element, realloc le
  tableau en enlevant l’elem.
*/

/*
  ETAPE 7 CD
  la, je me contenterait de vous dire "chdir". Et man. Et google.
*/

/*
  Et voila, t’as un super minishell !
  Merci, db0-lepage_b !
  Bisous ? Non...? Ok.
*/

// https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe



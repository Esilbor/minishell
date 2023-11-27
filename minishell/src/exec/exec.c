
// http://i.paysdu42.fr/?page=minishell.c

/*
  ETAPE 1 PROMPT
  faisons le simple principe d’afficher un prompt qui lit des
  commandes et fait rien (pour l’instant) puis qui se raffiche.
*/


/*
  ETAPE 2 LANCER UN PROGRAMME - RECUPERER LE PATH
  essayons de lancer un programme. Pour cela, nous utilisons execve.
  Cette fonction prend en parametre un path. Il faut donc commencer par
  trouver ce path. Pour cela, notre environnement nous fournit un element
  appele PATH.

  -- > faire un str_to_wordtab de ce qu’a renvoyer get_next_line.
  -- > faire une fonction qui recupere le contenu d’un element de l’env.



  //char*my_getenv(char **env, char *elem //"PATH" //)
//{
  // je parcours l’env, je trouve la ligne qui commence par PATH /
  // j’envoie l’adresse de ce qui se trouve apres le ’=’ /
//}

/  -- > faire une fonction qui recupere uns a uns les paths dans cet elem
    -- > faire une fonction qui ajoute a la suite du path recupere le
  element du tableau de str_to_wordtab.
    Tester ces paths avec la fonction access. Comment elle marche ? -> man
*/



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


/*

init data : initialisation de notre structure: 

ft_get_env(data, envp);



*/


#include "../includes/minishell.h"


int ft_nb_cmd(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

/*
//void    ft_init_data(t_data *data, char **envp)
void    ft_init_data(t_data *data, t_env *lst_env)
{

  //char			*get_env_value(t_env *envb, char **str);
 //t_env			*get_env_node(t_env *lst, char *str);

 *data = (t_data){0, 0, 0, 0, 0, 0,0 ,0};

 data->lst_env = get_env(&lst_env->var_str);
 data->cmd_path = ft_read_path(data);   // data->paths = a faire ;
 printf("data->cmd_path = %s\n", data->cmd_path);
//data->cmds = a faire;
// px->cmd = get_cmd(px, px->cmd_paths, px->cmd_args[0], env); pipex
// px->cmd_paths = ft_split(px->paths, ':');
data->paths = set_tab_paths(data);
//printf("data->paths = %s\n", data->paths);
//data->lexer= ft_lexer(data->cmd_line); // t_lexer	*ft_lexer(char *line)
//data->lst_cmd = command_builder(&data->lexer);
//data->cmds_nb = ft_nb_cmd(data->lexer->word); // cmd + builtins

}
*/

// void ft_isbuiltin(t_data *data, int index)
// {
  


// }
//void	ft_execution(t_data *data, char **envp)
void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void ft_path_ok_cmd(t_data *data, char **cmd, char **envp, int index)
{
    char *cmd_find;

    cmd_find = set_path_cmd(data, cmd[0]);
    if(!cmd_find)
    {
      //free , exit ?
    
     // ft_free_tab((void **)envp);
     printf(" cmd_path //  = %s\n", data->lst_cmd[index]->cmd[0]);
     ft_free_char_tab(envp);
    }
}


char    **env_to_tab(t_env *lst)
{
    
    printf("\n==========Ici dans la fonction ---> env_to_tab==========\n");
    int        i;
    int        len;
    char        **tab;

    i = 0;
    len = ft_lstsize((t_list *)lst);
    printf("len = %d\n", len);
   // tab = (char **)malloc(sizeof(char *) * (len + 1));
     //tab = (char **)malloc(sizeof(char *) * (4096)); // 64 *
    tab = malloc(sizeof(char *) * (len + 1));
    if (!tab)
    {
      printf("Unable to allocate memory.\n");
      exit(1);
       // return (NULL);
    }
      
    tab[len] = NULL;
    while (lst)
    {
        tab[i] = ft_strdup(lst->var_str);
        if (!tab[i])
            return (ft_free_tab((void **)tab), NULL);
        lst = lst->next;
        i ++;
    }
    return (tab);    
}



void	ft_print_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab !=NULL && *tab)
		{
			printf("tab[%d] = %s\n", i, (char *)tab[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("(NULL)\n");
}

void	ft_init_execution(t_data *data, int index)
{

  printf("---------------------ft_init_execution*****************\n");

  // init data , cmd ...

  // int	ft_fill_lexer(t_lexer **lexer_lst, char *cmd_line)

  //ft_init_data(data, lst_env);
  
  
  //printf("data->cmd_path = %s\n", data->cmd_path);

  char **envp;

  // data->paths = ft_split(data->path, ':');
  // if (!data->paths)
	// 		printf("ERR_SPLIT\n");


  // envp = ft_get_env(data); // , index);
  envp = env_to_tab(data->lst_env);
  printf("envp \n ft_print_char_tab = \n");
  ft_print_char_tab(envp);




	if (data->paths && !ft_strchr(data->lst_cmd[index]->cmd[0], '/'))
		ft_path_ok_cmd(data, data->lst_cmd[index]->cmd, envp, index);
	// else
	


}

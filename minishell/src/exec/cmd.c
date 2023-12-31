/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:57:33 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/26 16:04:02 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	string_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}

static char	*check_cmd_null(char *cmd)
{
	if (!cmd || string_empty(cmd))
	{
		return (ft_putstr_fd("CMD NULL", 2), NULL);
	}
	return (cmd);
}

//return true if cmd is a directory
bool	is_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf))
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (is_directory(cmd))
		ft_putstr_fd("is a directory\n", 2);
	else
		ft_putstr_fd("cmd_path not found\n", 2);
}

char *set_path_cmd(t_set *set, char *cmd)
{
	int index;
	char *tmp;
	char *cmd_tmp;

	cmd = check_cmd_null(cmd);
	index = 0;
	while (set->paths[index] && cmd)
	{
		tmp = ft_strjoin("/", cmd);
		if (!tmp)
			return (free_after_builtin(set),ft_putstr_fd("ERR_MAL\n", 2), NULL); // (1) ---> ?free + close tout ce qui a ete initialise/ malloc avant
		cmd_tmp = ft_strjoin(set->paths[index], tmp);
		if (!cmd_tmp)
			return (free(tmp),free_after_builtin(set),ft_putstr_fd("ERR_MAL\n", 2), NULL); // (2)
		if (access(cmd_tmp, X_OK | F_OK) == 0)		
			return (free(tmp),cmd_tmp);
		free(tmp);
		free (cmd_tmp);
		index++;
	}
	print_cmd_not_found(cmd);
	return (NULL);
}


// free tout ce qui a ete initialise/ malloc avant
// (1) (2) ---- > free_after_builtin(t_set *set) ?
/*

	-------------------------------------------------------------------
	t_set	*init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb)
	-------------------------------------------------------------------
	
	--> free_cmd_struct_tab(cmd_tab) // t_cmd **
	--> free (set) //  t_set
	--> free (set->paths) // char **
	--> free (set->envp) // char **
	--> 
	
	---------------------------------------------
	init_pipe_set(set);
	---------------------------------------------
	
	--> free (set->pipe[0]);
	--> free (set->pipe[1]);
	--> free (set->pipe);
	--> ft_close_pipes (t_set *set)

	--------------------------------
	void	init_pid_tab(t_set *set)
	---------------------------------

	--> free (set->pid )
	--> 

	----------------------------
	char	**env_to_tab(t_env *lst)
	---------------------------------
	--> free(lst)
	

	free_lexer_list(lexer) --- > shell_parser.c
		free_lexer_list(&(cmd_tab[i])->output);
		free_lexer_list(&(cmd_tab[i])->input);
		? free(cmd_tab[i]->heredoc_path);
	
*/





// free + close pipes
// free env
// free cmd_tab  -- > free_cmd_struct_tab(cmd_tab);



// void	free_cmd_struct_tab(t_cmd **cmd_tab)
// void	ft_free_tab(void **tab)
// void	free_redirections(t_cmd **tab)
// void	sugar_rush(t_set *set)
// void	ft_free_env_lst(t_env *env)
// void	free_lexer_list(t_lexer **head)
// void	ft_close_pipes(t_set *set)
// void	free_after_builtin(t_set *set)

/*

	void	sugar_rush(t_set *set)
	{
		free(set->pid);
		free(set->pipe[0]);
		free(set->pipe[1]);
		free(set->pipe);
		ft_free_tab((void **) set->paths);
		ft_free_tab((void **) set->envp);
		free_redirections(set->cmd_set);
		free_cmds((t_cmd **)set->cmd_set);
		free(set);
	}



	void	free_after_builtin(t_set *set)
	{
		ft_free_env_lst(set->env_lst);
		free(set->pipe[0]);
		free(set->pipe[1]);
		free(set->pipe);
		ft_free_tab((void **)set->paths);
		ft_free_tab((void **)set->envp);
		free_cmds((t_cmd **)set->cmd_set);
		free(set->pid);
		free (set);
	}



*/
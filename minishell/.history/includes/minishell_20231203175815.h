/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:45 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/03 17:58:15 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[31m"
# define GREEN "\033[92m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define YELLOW "\033[33m"
# define PINK "\033[38;2;255;105;180m"
# define ORANGE "\033[38;2;255;105;280m"
# define RESET "\x1B[0m"
# define PROMPT "\001\033[38;2;255;105;180m\002Candy_$hell> \001\033[33m\002"
# define PROMPT1 "\001\033[38;2;255;105;280m\0021_Candy_$hell> \001\033[35m\002"
# define PROMPT2 "\001\033[35m\0022_Candy_$hell> \001\033[34m\002"
# define PROMPT3 "\001\033[92m\002Candy_$hell?> \001\033[34m\002"
# define 

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// DO NOT MODIFY ORDER OF T_TOKENS
typedef enum e_tokens
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	GREAT_GREAT,
	LESS_LESS,
	DOLLAR,
	DQUOTE,
	SQUOTE,
	INPUT,
	OUTPUT,
	APPEND,
	LIMITER,
	EXPAND,
	SMERGE,
	DMERGE,
	WMERGE,
	EMERGE,
}	t_tokens;

typedef struct s_lexer
{
	char			*word;
	t_tokens		type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_env
{
	char			*var_str;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	int		index;
	char	**cmd;
	char	**eof; 
	bool	append;
	char	*heredoc_path;
	char	**input_redir;
	// char	**output_redir;
	t_lexer	*output;

}	t_cmd;

typedef struct t_set
{
	char			**paths;
	int				cmd_nb;
	struct s_env	*envb;
	struct s_cmd	**cmd_set;
}	t_set;



/******************************************/
/***************BUILT-IN*******************/
/******************************************/


int		do_exit(char **cmd_tab, t_env **envb);

/*	cd_echo_pwd_builtins.c	*/

int		do_cd(char **str, t_env **envb);
void	do_echo(int cmd_nb, char **str);
int		do_pwd(char **cmd_tab, t_env **env);

/*	env_display.c	*/

int		ft_print_rainbow(char *str);
void	print_env(t_env **head);
int		assign_or_append(char *env_var);
bool	cmd_is_valid(char **cmd_tab, int i, int *ret);

/*	env_management_1.c	*/

void	ft_free_env_lst(t_env *env);
t_env	*ft_last_env_node(t_env *node);
void	ft_add_env_node(t_env **env, char *varp);
t_env	**dup_env(t_env **env);
void	ft_fill_env(t_env **env, char **envp);

/*	env_management_2.c	*/

unsigned int	ft_rand(void);
void	init_colors(char **colors);
t_env	**sort_env(t_env **head);
t_env	*get_env(char **envp);

/*	export_handling_1.c	*/

void	create_var(char **v_tab, char **cmd_tab, t_env **env, int i);
void	modify_var(t_env *node, char **v_tab, char **cmd_tab, int i);
int		update_ret(t_env **env, int ret);
int		do_export(int cmd_nb, char **cmd_tab, t_env **env);

/*	export_handling_2.c	*/

t_env	*get_env_node(t_env *lst, char *str);
char	**ft_split_value(char *var);

/*	unset_builtin.c	*/

void	ft_remove_env_node(t_env **head, char *varp);
int		do_unset(char **cmd_tab, t_env **env);

/******************************************/
/*******************ENV********************/
/******************************************/

/*	env.c	*/

char	*ft_prompt(t_env *envb);


/******************************************/
/****************PARSING*******************/
/******************************************/

/*	command_builder.c	*/

t_cmd	**fill_cmd_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb, int tok_nb);
t_cmd	**fill_eof_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb, int tok_nb);
t_cmd	**fill_input_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb, int tok_nb);
t_cmd	**fill_output_lst(t_lexer *lex, t_cmd **str_tab, int cmd_nb);
t_cmd	**command_builder(t_lexer **lexer);

/*	command_utils.c	*/

int		count_cmd(t_lexer *lex);
t_cmd	**init_cmd_struct(t_lexer **lexer);
int		token_nb(t_lexer **lexer, t_tokens token);

/*	expansion_cleanup.c	*/

void	clean_lexer4(t_lexer **lexer);
void	clean_lexer(t_lexer **lexer);
void	clean_lexer2(t_lexer **lexer);
void	clean_lexer3(t_lexer **lexer);
void	clean_redir(t_lexer **lexer, t_lexer **lex, t_tokens type);
void	clean_squotes(t_lexer **lexer);

/*	expansion_merge.c	*/

void	merge_nodes(t_lexer **lexer);
t_lexer	*parsing(char *input, t_lexer **lexer, t_env *envb);
void	quotes_to_words(t_lexer **lexer);
void	ft_expander(t_lexer **lexer, t_env *envb);
void	lexer_polish(t_lexer **lexer);
t_lexer	**clean_empty_nodes(t_lexer **lexer);

/*	expansion_utils_1.c	*/

t_lexer	*ft_remove_lex_node(t_lexer **lexer, t_lexer *node_to_remove);
t_lexer	*expand_node(t_lexer **lexer, t_lexer *lst, t_env *envb);
t_lexer	*expand_node2(char *tmp, t_lexer *node, t_env *envb);
char	*extract_var(char *str, char **ptr);
char	*get_env_value(t_env *envb, char **str);

/*	expansion_utils_2.c	*/

char	*dol_to_expand(char *str);
t_lexer	*expand_dquote(char *tmp, t_lexer *node, t_env *envb);
t_lexer	*clean_quotes(t_lexer *node);

/*	expansion_handlers_1.c	*/

int		handle_squotes(char *cmd_line, int *i, t_lexer **head);
int		handle_dquotes(char *cmd_line, int *i, t_lexer **head);
void	handle_spec_chars(char *cmd_line, int *j, t_lexer **head);
void	handle_dollar(char *cmd_line, int *i, t_lexer **head);
void	handle_words_spec_char(char *cmd_line, int *i, t_lexer **head);

/*	expansion_handlers_2.c	*/

void	handle_non_quote(char *str, int *i, int *j, char *epur_str);
void	handle_quote(char *str, int *i, int *j, char *epur_str);

/*	lexer_spec_chars.c	*/

t_tokens	is_spec_char(char *c);
t_tokens	is_spec_char2(char *c);
t_tokens	is_spec_char3(char *c);
t_tokens	is_spec_char4(char *c);

/*	lexer_utils_1.c	*/

void 	free_lexer_list(t_lexer **head);
int 	is_wspace(char c);
int  	is_quote(char c);
char	*ft_epur_str(char *str);
int		ft_fill_lexer(t_lexer **lexer_lst, char *cmd_line);


/*	lexer_utils_2.c	*/

t_lexer *ft_last_lexer_node(t_lexer *node);
void 	ft_add_lex_node(t_lexer **lexer, char *word, t_tokens type);
t_lexer	*syntax_error(t_lexer *lexer, t_lexer **lexer_head);
t_lexer	*check_valid_input(t_lexer **lexer_head);
t_lexer	*ft_lexer(char *line);

	/*to be deleted */

char	*print_token(t_tokens token);
void 	print_lexer(t_lexer **head, char *loc);
void 	ft_print_struct_tab(t_cmd **struct_tab);


/******************************************/
/******************MAIN********************/
/******************************************/

void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	do_builtins(char **cmd_tab, t_env **envb);
void	ft_handle_signals(void);
void	ft_quit_shell(t_env *envb, t_cmd **cmd_struct_tab);
void	free_cmd_struct_tab(t_cmd **cmd_struct_tab);
void	free_shell(char **cmd_tab, t_lexer *lexer, char *input, t_cmd **cmd_struct_tab);
int		shell_loop(t_env *envb);
t_set   *init_set(t_set **set, t_cmd **cmd_struct_tab, t_env *envb);
char	**env_to_tab(t_env *lst);

#endif

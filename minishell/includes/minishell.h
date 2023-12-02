/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:45 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/02 21:05:44 by zaquedev         ###   ########.fr       */
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

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
}					t_tokens;

typedef struct s_lexer
{
	char			*word;
	t_tokens		type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_env
{
	char			*var_str;
	char *env_value; // valeur
	struct s_env	*next;
}					t_env;

// typedef struct s_cmd
// {
// 	int				index;
// 	char			**cmd;
// 	char			*eof;
// 	char			*heredoc_path;
// 	char			*input_redir;
// 	char			*output_redir;
// 	int				fd_out;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;

// }	t_cmd;

typedef struct s_cmd
{
	int				index;
	char **cmd; // tableau des [cmd + builtins]
	char			**eof;
	bool			append;
	char			*heredoc_path;
	char **input_redir; // derniers input des cmds
	// char	**output_redir;
	// liste des output a creer et a ecrire ds le dernier fd_out
	t_lexer			*output;
	int				fd_out;
	int				fd_in;

}					t_cmd;

// typedef struct t_set
// {
//     char            **paths;
//     int                cmd_nb;
//     struct s_env    *envb; // would give access to envb if needed
//     struct s_cmd    **cmd_set;
// would give access to cmd_struct_tab if needed
// }    t_set;

typedef struct s_data
{
	t_env			*lst_env;
	char			**env_arr;
	char			**paths;
	char			*path;
	char			*cmd_path;

	t_cmd			**lst_cmd;
	int				cmds_nb;
	int				exit;

	//char			*cmd_line; // char  *line;
	// data->line = readline("Candy_$hell$ ");
	// char			**builtins_tab;

	int				**pipes;
	int				*pid;
	int				fd[2];

	// char			*readline;
	// char			*cmds_exec;
	// pid_t			*pid;
	// struct s_token	*token;
	// struct s_cmd	**cmds;
	// struct s_env	*export;

}					t_data;

// LEXER

/*	cd_echo_pwd_builtins.c	*/

int					do_cd(char **str, t_env **envb);
void				do_echo(int cmd_nb, char **str);
int					do_pwd(char **cmd_tab, t_env **env);

/*	env_display.c	*/

int					ft_print_rainbow(char *str);
void				print_env(t_env **head);
int					assign_or_append(char *env_var);
bool				cmd_is_valid(char **cmd_tab, int i, int *ret);

/*	env_management_1.c	*/

void				ft_free_env_lst(t_env *env);
t_env				*ft_last_env_node(t_env *node);
void				ft_add_env_node(t_env **env, char *varp);
t_env				**dup_env(t_env **env);
void				ft_fill_env(t_env **env, char **envp);

/*	env_management_2.c	*/

unsigned int		ft_rand(void);
void				init_colors(char **colors);
t_env				**sort_env(t_env **head);
t_env				*get_env(char **envp);

/*	export_handling_1.c	*/

void				create_var(char **v_tab, char **cmd_tab, t_env **env,
						int i);
void				modify_var(t_env *node, char **v_tab, char **cmd_tab,
						int i);
int					update_ret(t_env **env, int ret);
int					do_export(int cmd_nb, char **cmd_tab, t_env **env);

/*	export_handling_2.c	*/

t_env				*get_env_node(t_env *lst, char *str);
char				**ft_split_value(char *var);

/*	unset_builtin.c	*/

void				ft_remove_env_node(t_env **head, char *varp);
int					do_unset(char **cmd_tab, t_env **env);

/******************************************/
/*******************ENV********************/
/******************************************/

/*	env.c	*/

char				*ft_prompt(t_env *envb);

/******************************************/
/****************PARSING*******************/
/******************************************/

/*	command_builder.c	*/

t_cmd				**fill_cmd_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb,
						int tok_nb);
t_cmd				**fill_eof_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb,
						int tok_nb);
t_cmd				**fill_input_tab(t_lexer *lex, t_cmd **str_tab, int cmd_nb,
						int tok_nb);
t_cmd				**fill_output_lst(t_lexer *lex, t_cmd **str_tab,
						int cmd_nb);
t_cmd				**command_builder(t_lexer **lexer);

/*	command_utils.c	*/

int					count_cmd(t_lexer *lex);
t_cmd				**init_cmd_struct(t_lexer **lexer);
int					token_nb(t_lexer **lexer, t_tokens token);

/*	expansion_cleanup.c	*/

void				clean_lexer(t_lexer **lexer);
void				clean_lexer2(t_lexer **lexer);
void				clean_lexer3(t_lexer **lexer);
void				clean_redir(t_lexer **lexer, t_lexer **lex, t_tokens type);
void				clean_squotes(t_lexer **lexer);

/*	expansion_merge.c	*/

void				merge_nodes(t_lexer **lexer);
void				quotes_to_words(t_lexer **lexer);
void				ft_expander(t_lexer **lexer, t_env *envb);

/*	expansion_utils_1.c	*/

t_lexer	*ft_remove_lex_node(t_lexer **lexer,
							t_lexer *node_to_remove);
t_lexer				*expand_node(t_lexer **lexer, t_lexer *lst, t_env *envb);
t_lexer				*expand_node2(char *tmp, t_lexer *node, t_env *envb);
char				*extract_var(char *str, char **ptr);
char				*get_env_value(t_env *envb, char **str);

/*	expansion_utils_2.c	*/

char				*dol_to_expand(char *str);
t_lexer				*expand_dquote(char *tmp, t_lexer *node, t_env *envb);
t_lexer				*clean_quotes(t_lexer *node);

/*	expansion_handlers_1.c	*/

int					handle_squotes(char *cmd_line, int *i, t_lexer **head);
int					handle_dquotes(char *cmd_line, int *i, t_lexer **head);
void				handle_spec_chars(char *cmd_line, int *j, t_lexer **head);
void				handle_dollar(char *cmd_line, int *i, t_lexer **head);
void				handle_words_spec_char(char *cmd_line, int *i,
						t_lexer **head);

/*	expansion_handlers_2.c	*/

void				handle_non_quote(char *str, int *i, int *j, char *epur_str);
void				handle_quote(char *str, int *i, int *j, char *epur_str);

/*	lexer_spec_chars.c	*/

t_tokens			is_spec_char(char *c);
t_tokens			is_spec_char2(char *c);
t_tokens			is_spec_char3(char *c);
t_tokens			is_spec_char4(char *c);

/*	lexer_utils_1.c	*/

void				free_lexer_list(t_lexer **head);
int					is_wspace(char c);
int					is_quote(char c);
char				*ft_epur_str(char *str);
int					ft_fill_lexer(t_lexer **lexer_lst, char *cmd_line);

/*	lexer_utils_2.c	*/

t_lexer				*ft_last_lexer_node(t_lexer *node);
void				ft_add_lex_node(t_lexer **lexer, char *word, t_tokens type);
t_lexer				*syntax_error(t_lexer *lexer, t_lexer **lexer_head);
t_lexer				*check_valid_input(t_lexer **lexer_head);
t_lexer				*ft_lexer(char *line);

/*to be deleted */

char				*print_token(t_tokens token);
//void 	print_lexer(t_lexer **head, char *loc);

void				print_lexer(t_lexer **head, char *loc);

void				ft_print_struct_tab(t_cmd **struct_tab);

/******************************************/
/******************MAIN********************/
/******************************************/

void				sigint_handler(int signum);
void				sigquit_handler(int signum);
void				do_builtins(char **cmd_tab, t_env **envb);
void				ft_handle_signals(void);
void				ft_quit_shell(t_env *envb, t_cmd **cmd_struct_tab);
void				free_cmd_struct_tab(t_cmd **cmd_struct_tab);
void				free_shell(char **cmd_tab, t_lexer *lexer, char *input,
						t_cmd **cmd_struct_tab);
//int		shell_loop(t_env *envb);
int					shell_loop(t_env *envb, char **envp);

// CMDS

//void	ft_execution(t_data *data, t_env *envp);
//void    ft_init_data(t_data *data, t_env *lst_env);

t_data				*init_set(t_data **data, t_cmd **cmd_struct_tab,
						t_env *envb);

// PATH // cmd_path

char				*ft_get_path(t_env *envb);
char				*check_cmd(t_data *data, char *cmd);

int					ft_nb_cmd(char *str);

// void	ft_isbuiltin(t_data *data, int index, char *argv[]);

// ft_print_tab --> libft
// voir expand_dquote pour l'utilisation du get_env_value

char				*set_path_cmd(t_data *data, char *cmd);
void				ft_init_execution(t_data *data, int index);
char				**env_to_tab(t_env *lst);
void				ft_print_char_tab(char **tab);

// pre-processing
int					check_first(t_data *data, int argc, char **envp);

// int ft_exexution(t_data *data);
// int exec_cmd(t_data *data);

//void run_execution(t_data *data);
int					run_execution(t_data *data, t_cmd **cmd_struct_tab);
int					**init_pipes(t_data *data);
void				init_fd(int **fd, t_cmd *cmd, int index);
int					**pipes_alloc(t_data *data);
int					is_builtin(char **command);
int					ft_fork(t_data *data, int index);
void				ft_exec_cmd(t_data *data, int index);
int					ft_stdin(t_data *data, int index);
int					ft_stdout(t_data *data, int index);
int					pid_alloc(t_data *data);
#endif

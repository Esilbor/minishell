/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:45 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/07 20:02:18 by bbresil          ###   ########.fr       */
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

typedef enum e_tokens
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	LESS_LESS,
	GREAT_GREAT,
	DOLLAR,
	DQUOTE,
	SQUOTE,
	INPUT,
	OUTPUT,
	LIMITER,
	EXPAND,
}	t_tokens;

typedef struct s_lexer
{
	char			*word;
	t_tokens		type;
	// int			i;
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
	int				index;
	char			**cmd;
	char			*eof;
	char			*heredoc_path;
	char			*input_redir;
	char			*output_redir;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;

}	t_cmd;

// LEXER
void			handle_words_spec_char(char *cmd_line, int *i, t_lexer **head);
void			handle_dollar(char *cmd_line, int *i, t_lexer **head);
void			print_lexer(t_lexer **head);
void			free_lexer_list(t_lexer **head);
t_lexer			*ft_lexer(char *line);
char			*ft_epur_str(char *str);
int				is_wspace(char c);
int				ft_cmd_count(char *str);


// EXPAND

void			ft_expander(t_lexer **lexer, t_env *envb);
t_lexer			*expand_node(t_lexer **lexer, t_lexer *lst, t_env *envb);
void 			expand_dquote(/* t_lexer **lexer, */ t_lexer *lst/* , t_env *envb */);
// BUILT-INS

int				do_pwd(char **cmd_tab, t_env **envb);
void			do_echo(int cmd_nb, char **str);
int				do_cd(char **str, t_env **envb);
int				do_export(int cmd_nb, char **cmd_tab, t_env **env);
int				do_unset(char **cmd_tab, t_env **env);
void			print_err(char *invalid_cmd, char *cmd_name);
char			**ft_split_value(char *var);
int				assign_or_append(char *env_var);

// ENV_FUNCTIONS

char			*ft_prompt(t_env *envb);
t_env			**dup_env(t_env **env);
t_env			*ft_last_env_node(t_env *node);
void			ft_add_env_node(t_env **env, char *varp);
void			ft_fill_env(t_env **env, char **envp);
void			print_env(t_env **head);
t_env			*get_env_node(t_env *lst, char *str);
t_env			*get_env(char **envp);
void			ft_remove_env_node(t_env **head, char *varp);
t_env			**sort_env(t_env **head);
void			ft_free_env_lst(t_env *env);
int				update_ret(t_env **env, int ret);
void			modify_var(t_env *node, char **v_tab, char **cmd_tab, int i);
void			create_var(char **v_tab, char **cmd_tab, t_env **env, int i);
bool			cmd_is_valid(char **cmd_tab, int i, int *ret);

// SIGNALS
void			sigint_handler(int signum);
void			sigquit_handler(int signum);
void			ft_handle_signals(void);

// COLORS
void			init_colors(char **colors);
// char			*ft_rand_col(void);
unsigned int	ft_rand(void);

#endif

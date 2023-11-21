# Minishell Function Organization

This document outlines the reorganized structure for the Minishell project, detailing the distribution of functions across various files. Each file contains a maximum of five functions, grouped logically based on their usage.

## Built-in Commands

### File: `env_management.c`
- Functions primarily dealing with environment variables from `do_env.c`
  - `ft_free_env_lst`
  - `ft_add_env_node`
  - `ft_fill_env`
  - `ft_rand`
  - `init_colors`

### File: `env_display.c`
- Functions for displaying environment settings, from `do_env.c` and `do_export.c`
  - `ft_print_rainbow`
  - `print_env`
  - `assign_or_append`
  - `print_err`
  - `cmd_is_valid`

### File: `export_handling.c`
- Functions focused on export command in `do_export.c`
  - `create_var`
  - `modify_var`
  - `update_ret`
  - `do_export`

### File: `cd_echo_commands.c`
- Functions from `do_cd.c` and `do_echo.c` related to 'cd' and 'echo' commands
  - `do_cd`
  - `if` (from `do_cd.c`)
  - `do_echo`

### File: `unset_command.c`
- Functions from `do_unset.c` related to 'unset' command
  - `ft_remove_env_node`
  - `do_unset`

## Parsing

### File: `expansion_cleanup.c`
- Functions from `expand.c` for cleaning up during expansion
  - `clean_lexer3`
  - `clean_redir`
  - `clean_lexer2`
  - `clean_squotes`
  - `clean_lexer`

### File: `expansion_merge.c`
- Functions from `expand.c` for merging and expanding
  - `merge_lex_nodes`
  - `merge_nodes`
  - `quotes_to_words`
  - `ft_expander`
  - `if` (from `expand.c`)

### File: `lexer_initialization.c`
- Initial set of functions from `lexer.c` for lexer setup
  - `free_lexer_list`
  - `is_wspace`
  - `is_quote`
  - `handle_non_quote`
  - `handle_quote`

### File: `lexer_spec_chars.c`
- Functions from `lexer.c` dealing with special characters
  - `is_spec_char2`
  - `is_spec_char3`
  - `is_spec_char`
  - `ft_add_lex_node`
  - `handle_squotes`

### File: `lexer_handling.c`
- Functions from `lexer.c` for handling various lexer scenarios
  - `handle_dquotes`
  - `handle_spec_chars`
  - `handle_dollar`
  - `handle_words_spec_char`
  - `ft_fill_lexer`

### File: `lexer_display.c`
- Remaining functions from `lexer.c` and `command_builder.c` for lexer display and command count
  - `print_lexer`
  - `count_cmd`
  - `token_nb`

### File: `command_printing.c`
- Functions from `print.c` for printing command structures
  - `ft_print_struct_tab`

## Environment and Execution Handling

### File: `env_exec_management.c`
- Can include leftover functions or new functions related to environment (`env.c`) and execution (`exec.c`).
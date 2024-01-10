MAKEFLAGS += --no-print-directory

# project
NAME = minishell

# compiler
CC = cc
CFLAGS = -g2 -Wall -Wextra -Werror -pthread

# libft
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

#candyshop
COLORS = 91 92 93 94 95 96 95clear
RANDOM_COLOR = \e[$(shell echo $(COLORS) | tr ' ' '\n' | shuf -n 1)m
LAY_OUT_FILE = ./art.txt

# include
INC_LIB = -I./libft/
INC = -I./includes/

SRC_DIR = ./src/
OBJ_DIR = ./obj/
# sources and objects
# Define subdirectories
SRC_SUBDIRS = built-in env exec parsing

# Find all C source files in the src directory and its subdirectories
C_FILES = $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)$(dir)/*.c))
C_FILES += $(wildcard $(SRC_DIR)*.c) # Don't forget the files in the root of src/

# Define the object files based on the C source files
OBJ = $(C_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# The main target
all : $(LIBFT) $(NAME)

# Compiles libft
$(LIBFT) :
	@make -sC $(LIBFT_PATH)

# Pattern rule for object files needs to create subdirectories as necessary
$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Linking the project
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC_LIB) -L$(LIBFT_PATH) -lft -L$(LIBFT_PATH)ft_printf/ -lftprintf -lreadline

# Cleans object files
clean :
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_PATH)

# Cleans everything that has been created
fclean : clean
	@rm -rf $(NAME)
	@make fclean -sC $(LIBFT_PATH)

# Re-makes everything
re : fclean all

# These targets do not create any files
.PHONY: re clean fclean all show_lay_out

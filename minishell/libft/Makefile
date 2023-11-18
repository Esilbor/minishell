# project
NAME = libft.a

# compiler
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

FT_PRINTF_PATH = ./ft_printf/
# source files
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
ft_toupper.c ft_tolower.c ft_atoi.c ft_strlcat.c ft_memset.c ft_bzero.c \
ft_memcpy.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_memcmp.c ft_strnstr.c \
ft_memchr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strncmp.c ft_strjoin.c ft_strtrim.c \
ft_itoa.c ft_putchar_fd.c ft_strmapi.c ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_split.c ft_atol.c ft_free_tab.c ft_free_n_tab.c ft_strndup.c \
ft_tab_len.c ft_strcmp.c ft_strccmp.c ft_strlen3.c\
$(FT_PRINTF_PATH)ft_printf.c ft_is_c.c ft_strsjoin.c ft_strccpy.c ft_strpcpy.c\
ft_print_tab.c \

OBJ_DIR = ./obj/
FT_PRINTF_NAME = libftprintf.a
FT_PRINTF = $(addprefix $(FT_PRINTF_PATH), $(FT_PRINTF_NAME))

# OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c

BONUS_OBJ = $(addprefix $(OBJ_DIR), $(BONUS:.c=.o))

all : $(FT_PRINTF)
$(FT_PRINTF): $(NAME)

$(FT_PRINTF) :
	@make -sC $(FT_PRINTF_PATH)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR)ft_printf%.o : $(FT_PRINTF_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I. -I$(FT_PRINTF_PATH) -c $< -o $@

$(OBJ_DIR)$(FT_PRINTF_PATH)%.o : $(FT_PRINTF_PATH)%.c
	@mkdir -p $(OBJ_DIR)$(FT_PRINTF_PATH)
	@$(CC) $(CFLAGS) -I. -I$(FT_PRINTF_PATH) -c $< -o $@


$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus : $(OBJ) $(BONUS_OBJ)
	ar rc $(NAME) $(OBJ) $(BONUS_OBJ)

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(FT_PRINTF_PATH)

fclean : clean
	@rm -rf $(NAME)
	@make fclean -sC $(FT_PRINTF_PATH)

re : fclean all

.PHONY: re clean fclean all bonus

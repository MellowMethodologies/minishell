SRCS_2 = ./parsing/exec.c ./parsing/lexer.c ./parsing/list_utils.c ./parsing/lexer.c \
		./parsing/lst.c ./parsing/free_functionss.c ./parsing/redirections.c\
		./parsing/heredoc.c ./parsing/checkers.c ./parsing/utils.c ./parsing/parse.c\
		./parsing/global_used_utils.c ./parsing/lexer_functions.c ./parsing/signals.c

SRCS=$(SRCS_LIBFT) $(SRCS_BUILTINS) $(SRCS_2)


SRCS_LIBFT = ./libft/ft_itoa.c ./libft/ft_split.c ./libft/ft_strmapi.c ./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c ./libft/ft_striteri.c\
			./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_strtrim.c ./libft/ft_strjoin.c ./libft/ft_atoi.c ./libft/ft_bzero.c\
			./libft/ft_calloc.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c\
			./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_strchr.c\
			./libft/ft_strdup.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strncmp.c ./libft/ft_strcmp.c ./libft/ft_strnstr.c\
			./libft/ft_strrchr.c ./libft/ft_tolower.c ./libft/ft_toupper.c ./libft/ft_substr.c


SRCS_BUILTINS=  ./builtins/check_error_bonus.c\
				./builtins/env.c\
				./builtins/env_two.c\
				./builtins/ft_cd.c\
				./builtins/ft_echo.c\
				./builtins/ft_execution.c\
				./builtins/ft_execution_one.c\
				./builtins/ft_execution_three.c\
				./builtins/ft_execution_two.c\
				./builtins/ft_export.c\
				./builtins/ft_export_one.c\
				./builtins/ft_export_three.c\
				./builtins/ft_export_two.c\
				./builtins/ft_lstadd_backn.c\
				./builtins/ft_lstnewn.c\
				./builtins/ft_pwd.c\
				./builtins/ft_read_bonus.c\
				./builtins/ft_split_bonus.c\
				./builtins/ft_unset.c\
				./builtins/paths_bonus.c\
				./builtins/ft_execution_one_v1.c\
				./builtins/ft_execution_one_v3.c\
				./builtins/ft_execution_one_v2.c\
				./builtins/ft_execution__v4.c


OBJS := $(SRCS:.c=.o)
CC  = cc
CFLAGS = -I/USERS/isbarka/.brew/opt/readline/include -lreadline -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -lreadline -L/USERS/isbarka/.brew/opt/readline/lib -lhistory -o $(NAME)

%.o: %.c mini_shell.h 
	$(CC) -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
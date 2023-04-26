
SRCS =	check_error_bonus.c env.c ft_bzero.c ft_calloc.c main.c ft_cd.c ft_echo.c ft_execution.c ft_export.c ft_lstadd_back.c ft_lstnew.c ft_putstr_fd.c ft_pwd.c ft_read_bonus.c ft_split.c ft_split_bonus.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strncmp.c ft_strrchr.c ft_unset.c paths_bonus.c
OBJS = $(SRCS:.c=.o)
CC  = cc
NAME = builtins.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -r $@ $^

%.o: %.c libft.h
	$(CC) -c  $<

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
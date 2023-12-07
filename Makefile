SRCS = src/main.c src/utils.c src/exec/cd.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

all : $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -lreadline $^ -o $@

%.o : %.c srcs/minishell.h
	cc $(CFLAGS) -lreadline -c $< -o $@

clean :
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re : fclean all
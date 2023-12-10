

SRCS = src/main.c src/utils.c src/cmds/ls.c src/cmds/echo.c src/utils/utils1.c
OBJS = $(patsubst src/%.c,src/objs/%.o,$(SRCS))
CFLAGS = -Wall -Wextra -Werror 
NAME = minishell

all : obj_folder $(NAME)

obj_folder:
	mkdir -p src/objs

$(NAME): $(OBJS)
	cc $(CFLAGS) -lreadline $^ -o $@

src/objs/%.o : src/%.c src/minishell.h
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -rf srcs/objs
fclean: clean
	rm -f $(NAME)
re : fclean all

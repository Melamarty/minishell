DIR = src
SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:.c=.o)
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
READLINE_L = $(shell ~/homebrew/bin/brew --prefix readline)/lib
READLINE_I = $(shell ~/homebrew/bin/brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $@ $(OBJS) $(LIBS) -L $(READLINE_L) #-fsanitize=address 

%.o: %.c src/minishell.h
	cc $(CFLAGS) -I $(READLINE_I) -c $< -o $@ 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
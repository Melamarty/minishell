SRCS = src/cmds/builtin.c src/cmds/cd.c src/cmds/echo.c src/cmds/env.c src/cmds/exit.c src/cmds/export.c src/cmds/pwd.c src/cmds/unset.c src/exec/exec_cmd.c src/exec/exec_line.c src/exec/handel_pipe.c src/exec/redirect.c src/expanding/expand_args.c src/expanding/ft_expand.c src/expanding/wildcard.c src/main.c src/parsing/env.c src/parsing/env2.c src/parsing/export_parse.c src/parsing/ft_itoa.c src/parsing/heredoc.c src/parsing/lstfunctions.c src/parsing/parsing_utils1.c src/parsing/parsing_utils2.c src/parsing/syntax_check.c src/parsing/syntax_check1.c src/parsing/syntax_check2.c src/parsing/token.c src/parsing/tokenizing0.c src/parsing/tokenizing1.c src/parsing/tree_creation1.c src/parsing/tree_creation2.c src/parsing/tree_creation3.c src/parsing/tree_utils.c src/utils/errors.c src/utils/export_utils.c src/utils/ft_atoi.c src/utils/ft_lstlen.c src/utils/ft_split.c src/utils/ft_strdup.c src/utils/ft_strrchr.c src/utils/ft_substr.c src/utils/gnl/get_next_line.c src/utils/list_utils.c src/utils/my_malloc.c src/utils/my_split.c src/utils/redirect_utils.c src/utils/set_arr.c src/utils/utils.c src/utils/utils1.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $@ $(OBJS) $(LIBS) -L $(READLINE_L)

%.o: %.c src/minishell.h
	cc $(CFLAGS) -I $(READLINE_I) -c $< -o $@ 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
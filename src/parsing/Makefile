SRCS = lstfunctions.c env.c parsing_utils1.c test.c tree_utils.c tree_creation.c token.c 
OBJS = $(SRCS:.c=.o)
NAME = minimashishell

all : $(NAME) clean

%.o : %.c
	cc -c $< -o $@

$(NAME) : $(OBJS)
	cc $(OBJS) -o $(NAME) -lreadline -fsanitize=address

clean : 
	rm -f $(OBJS)


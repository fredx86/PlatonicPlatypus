SRCS	=	 unit.c		\
		../select.c	\
		../llist.c	\
		../time_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= unitary

CC	= gcc

CFLAGS	= -Wall -Wextra -pedantic -g

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

SRCS	=	 unit.c		\
		../hmap.c	\
		../llist.c

OBJS	= $(SRCS:.c=.o)

NAME	= unitary

CC	= gcc

CFLAGS	= -Wall -Wextra -pedantic

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

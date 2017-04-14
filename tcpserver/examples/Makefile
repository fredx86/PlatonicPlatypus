SRCS	=	 ascii.c

OBJS	= $(SRCS:.c=.o)

NAME	= example

CC	= gcc

CFLAGS	= -Wall -Wextra -pedantic

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) ../libppts.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

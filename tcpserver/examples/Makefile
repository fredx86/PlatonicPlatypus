SRCS	=	 ascii.c	\
		../barray.c	\
		../byte_utils.c	\
		../llist.c	\
		../packet.c	\
		../select.c	\
		../socket.c	\
		../time_utils.c	\
		../tserver.c

OBJS	= $(SRCS:.c=.o)

NAME	= example

CC	= gcc

CFLAGS	= -Wall -Wextra -pedantic

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

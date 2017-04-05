SRCS	=	tserver.c	\
		select.c	\
		llist.c		\
		timeutils.c	\
		socket.c	\
		packet.c	\
		barray.c	\
		byteutils.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	libppts.a

CC	=	gcc

CFLAGS	=	-Wall -Wextra -pedantic

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

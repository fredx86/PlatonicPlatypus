SRCS	=	socket.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	libppso.a

CC	=	gcc

CFLAGS	=	-Wall -Wextra -pendantic

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

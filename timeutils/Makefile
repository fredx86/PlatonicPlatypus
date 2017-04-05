SRCS	=	timeutils.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	libpptu.a

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

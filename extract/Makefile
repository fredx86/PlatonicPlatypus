SRCS	=	extract.c	\
		barray.c	\
		byteutils.c	\
		strutils.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	libppex.a

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

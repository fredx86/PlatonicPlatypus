SRCS          = srcs/allocator.c				\
								srcs/barray.c						\
								srcs/clist.c						\
								srcs/hmap.c							\

OBJS          = $(SRCS:.c=.o)

NAME          = libpp.a

CC            = gcc

INCLUDES      = -I includes

CFLAGS      	= -Wall -Wextra $(INCLUDES) -Ofast

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

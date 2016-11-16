SRCS          = srcs/array.c						\
								srcs/allocator.c				\
								srcs/barray.c						\
								srcs/clist.c						\
								srcs/hmap.c							\
								srcs/net.c							\
								srcs/slcmgr.c						\
								srcs/socket.c						\
								srcs/utils.c						\

OBJS          = $(SRCS:.c=.o)

TESTS_SRCS		= tests/main.c						\
								tests/hmap.c						\

TESTS_OBJS		= $(TESTS_SRCS:.c=.o)

TEST_NAME			= assert

NAME          = libpp.a

CC            = gcc

INCLUDES      = -I includes

CFLAGS      	= -Wall -Wextra $(INCLUDES) -Ofast

test: all $(TESTS_OBJS)
	$(CC) -o $(TEST_NAME) $(TESTS_OBJS) $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TESTS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

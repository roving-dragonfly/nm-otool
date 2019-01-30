NAME = nm-otool
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =	srcs/test.c \
	srcs/endianess.c

OBJS = $(SRCS:.c=.o)
INCLUDES = -I./includes
RM = rm -f

.c.o:
	$(CC) $(FLAGS) -fPIC $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(INCLUDES) -o $(NAME) $^ ./libft/libft.a 

clean:
	make -C ./libft/ clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./libft/ fclean
	$(RM) $(NAME)

re: fclean all


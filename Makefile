NM = ft_nm
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =	srcs/nm.c \
        srcs/file_handling.c \
	srcs/file_mapping.c \
	srcs/parse_cl.c

OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/
INCLUDES = -I./includes -I./libft/includes
LFT = -L./libft -lft
RM = rm -f

.c.o:
	$(CC) $(FLAGS) -fPIC $(INCLUDES) -o $@ -c $<

all: $(NM)

$(NM): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(INCLUDES) -o $(NM) $^ $(LFT)

clean:
	make -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NM)

re: fclean all

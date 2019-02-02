NM = ft_nm
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NM_SRCS =	srcs/nm/file_handling.c \
		srcs/nm/file_mapping.c \
		srcs/nm/nm.c \
		srcs/nm/parse_file.c \
                srcs/nm/parse_cl.c \
		srcs/nm/parse_fat_header.c \
                srcs/nm/parse_macho_header.c \
                srcs/nm/parse_load_commands.c \
		srcs/nm/cleanup.c \
		srcs/nm/swapping/swap_tab.c \
		srcs/nm/swapping/swap_uint32.c \
		srcs/nm/swapping/swap_uint64.c 

NM_OBJS = $(NM_SRCS:.c=.o)
LIBFT = ./libft/
INCLUDES = -I./includes -I./libft/includes
LFT = -L./libft -lft
RM = rm -f

.c.o:
	$(CC) $(FLAGS) -fPIC $(INCLUDES) -o $@ -c $<

all: $(NM)

$(NM): $(NM_OBJS)
	make -C $(LIBFT)
	$(CC) $(INCLUDES) -o $(NM) $^ $(LFT)

clean:
	make -C $(LIBFT) clean
	$(RM) $(NM_OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NM)

re: fclean all

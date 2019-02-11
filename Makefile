NM = ft_nm
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NM_SRCS =	srcs/nm/file_handling.c \
		srcs/nm/file_mapping.c \
		srcs/nm/nm.c \
		srcs/nm/parse_file.c \
                srcs/nm/parse_cl.c \
                srcs/nm/parse_fat_header.c \
		srcs/nm/parse_fat_arch.c \
                srcs/nm/parse_macho_header.c \
                srcs/nm/parse_load_commands.c \
                srcs/nm/explore_fat_archs.c \
		srcs/nm/parse_static_lib_header.c \
                srcs/nm/parse_symbol_table.c \
		srcs/nm/extract_static_symbols.c \
                srcs/nm/extract_symbols.c \
                srcs/nm/parse_symtable.c \
                srcs/nm/parse_segments.c \
                srcs/nm/parse_sections.c \
		srcs/nm/parse_symbol_data.c \
                srcs/nm/populate_symtable.c \
                srcs/nm/sort_symlist.c \
                srcs/nm/print_symbols.c \
                srcs/nm/print_type.c \
		srcs/nm/arch_data.c \
		srcs/nm/print_arch_infos.c \
		srcs/nm/cleanup.c \
		srcs/nm/swapping/swap_tab.c \
		srcs/nm/swapping/swap_uint16.c \
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

NM = ft_nm
OTOOL = ft_otool
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address 
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
		srcs/nm/populate_macho_lst.c \
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

OTOOL_SRCS =	srcs/otool/cleanup.c \
		srcs/otool/ft_otool.c \
                srcs/otool/parse_cl.c \
		srcs/otool/arch.c \
		srcs/otool/parse_fat_arch.c \
		srcs/otool/parse_fat_header.c \
		srcs/otool/print_fat_header.c \
                srcs/otool/print_macho_header.c \
		srcs/otool/print_text_segment.c \
		srcs/otool/parse_symbol_table.c \
		srcs/otool/parse_file.c \
		srcs/otool/parse_load_commands.c \
		srcs/otool/parse_macho_header.c \
		srcs/otool/parse_sections.c \
                srcs/otool/parse_segments.c \
                srcs/otool/file_handling.c \
		srcs/otool/file_mapping.c \
		srcs/otool/explore_fat_archs.c \
		srcs/otool/parse_static_lib_header.c \
		srcs/otool/explore_static_symbols.c \
		srcs/otool/populate_macho_lst.c \
		srcs/otool/swapping/swap_tab.c \
		srcs/otool/swapping/swap_uint16.c \
		srcs/otool/swapping/swap_uint32.c \
		srcs/otool/swapping/swap_uint64.c 

OTOOL_OBJS = $(OTOOL_SRCS:.c=.o)

LIBFT = ./libft/
INCLUDES = -I./includes -I./libft/includes
LFT = -L./libft -lft
RM = rm -f

.c.o:
	$(CC) $(FLAGS)  $(INCLUDES) -o $@ -c $< 

all: $(NM) $(OTOOL)

$(NM): $(NM_OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NM) $^ $(LFT)

$(OTOOL): $(OTOOL_OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OTOOL) $^ $(LFT)

clean:
	make -C $(LIBFT) clean
	$(RM) $(NM_OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NM)

re: fclean all

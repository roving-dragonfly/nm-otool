/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 01:39:29 by aalves            #+#    #+#             */
/*   Updated: 2019/02/15 12:03:37 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <inttypes.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

//debug
#include <stdio.h>

# define T_OPEN_FAILED 1
# define T_CLOSE_FAILED 2
# define T_FSTAT_FAILED 3
# define T_MMAP_FAILED 4
# define T_MUNMAP_FAILED 5
# define T_PARSING_FAILED 6
# define T_CORRUPT_FILE 7

# define T_STATIC_MAGIC 0x213C617263683E0A
# define T_STATIC_CIGAM 0X0A3E686372613C21

# define T_OTOOL_FLAGS "tfh"

# define T_TEXT_FLAG		0x0000000000000001
# define T_FAT_FLAG			0x0000000000000002
# define T_MACHO_FLAG		0x0000000000000004

struct	s_proc_infos
{
	uint64_t		flags;
	uint64_t		n_files;
	char			**files;

};
typedef	struct s_proc_infos t_proc_infos;

struct	s_arch
{
    cpu_type_t					type;
	cpu_subtype_t				sub;
};
typedef struct s_arch t_arch;

struct	s_binfile
{
	char					*filename;
    void					*start;
	void					*end;
	t_arch					*arch;
	uint64_t				multi_arch;
	char					*obj;
	uint64_t				ar;
};
typedef	struct s_binfile t_binfile;

struct	s_symbol
{
	uint64_t					is64;
	char						*name;
	char						*obj;
	struct s_arch				arch;
	struct symtab_command		*symtab;
	void						*section;
	union u_nlist
	{
		struct nlist			n32;
		struct nlist_64			n64;
	}							nlist;
};
typedef struct s_symbol t_symbol;

struct	s_fat
{
	t_binfile					*file;
	struct fat_header			hdr;
	uint64_t					is64;
	void						*arch_start;
	union u_arch
	{
		struct fat_arch			fat32;
		struct fat_arch_64		fat64;
	}							**arch;
	struct s_swap				*s;
};
typedef struct s_fat t_fat;

struct	s_macho
{
	t_binfile					*file;
	union u_macho_header
	{
		struct mach_header		hdr32;
		struct mach_header_64	hdr64;
	}							hdr;
	uint64_t					is64;
	struct s_swap				*s;
	void						*lc_start;
	void						**lc_tab;
	t_list						*seg_list;
};
typedef	struct s_macho t_macho;

struct	s_segment
{
	union u_segment
	{
		struct segment_command		s32;
		struct segment_command_64	s64;
	}								seg;
	uint64_t						is64;
    void							*pos;
	void							**sect_tab;
};
typedef	struct s_segment t_segment;

struct	s_static_o
{
    void						*start;
    char						*name;
};
typedef struct s_static_o t_static_o;

struct	s_static_lib
{
	t_binfile					*file;
	struct s_swap				*s;
	void						*sym_start;
	void						*str_start;
    t_list						*macho_lst;
};
typedef	struct s_static_lib t_static_lib;

union	u_metadata
{
    t_macho						macho;
	t_fat						fat;
	t_static_lib				ar;
};

/*
** ft_otool.c
*/
int				main(int argc, char**argv);
int				ft_otool(t_proc_infos *pi, t_binfile *file);

/*
** parse_cl.c
*/
t_proc_infos   	*parse_cl(int argc, char **argv);

/*
** file_handling.c
*/
int				open_file(char *filename);
int				close_file(t_binfile *file, int fd);

/*
** file_mapping.c
*/
void			*map_file(t_binfile *file, int fd);
int				unmap_file(t_binfile *file);

/*
** parse_file.c
*/
int				 parse_file(t_proc_infos *pi, t_binfile *file, void *start);

/*
** parse_fat_header.c
*/
int				parse_fat_header(t_binfile *file, t_fat *metadata, void *start);

/*
** parse_static_lib_header.c				  
*/
int				parse_static_lib_header(t_binfile *file, t_static_lib *metadata, void *start);

/*
** parse_fat_arch.c
*/
int				parse_fat_arch(t_fat *meta);

/*
** print_fat_header.c
*/
void			print_fat_header(t_proc_infos *pi, t_fat *meta);

/*
** print_macho_header.c
*/
void			print_macho_header(t_macho *meta);

/*
** print_macho_header.c
*/
void			print_text_segment(t_macho *meta);

/*
** parse_macho_header.c
*/
int				parse_macho_header(t_binfile *file, t_macho *metadata, void *start);

/*
** parse_load_commands.c
*/
int				parse_load_commands(t_macho *meta);

/*
** explore_fat_archs.c
*/
int				explore_fat_archs(t_proc_infos *pi, t_fat *meta);
/*
** parse_segments.c
*/
int				parse_segments(t_macho *meta);

/*
** parse_sections.c
*/
int				parse_sections(t_macho *meta, t_segment *seg);

/*
** parse_symbol_table.c
*/
int				parse_symbol_table(t_static_lib *meta);

/*
** extract_static_symbols.c
*/
int				explore_static_symbols(t_proc_infos *pi, t_static_lib *meta);
int				explore_by_crappy_jumps(t_proc_infos *pi, t_static_lib *meta);
/*
** populate_macho_lst.c
*/
int				populate_macho_lst(t_static_lib *meta);

/*
** arch.c
*/
void			get_default_arch(t_fat *meta);

/*
** cleanup.c
*/
void			cleanup_binfile(t_binfile *file);
void			cleanup_macho(t_macho *meta);
void			cleanup_fat(t_fat *meta);
void			cleanup_static(t_static_lib *meta);

/*
** Swapping interface
*/
struct	s_swap
{
	const struct s_swap_interface *tab;
};
typedef struct s_swap t_swap;

struct	s_swap_interface
{
	uint16_t	(*swap_uint16)(uint16_t);
    uint32_t	(*swap_uint32)(uint32_t);
	uint64_t	(*swap_uint64)(uint64_t);
};

t_swap	*noswap_tab(void);
t_swap	*swap_tab(void);

uint32_t	swap_uint32(t_swap *s, uint32_t n);
uint32_t	rev_uint32(uint32_t n);
uint32_t	std_uint32(uint32_t n);

uint64_t	swap_uint64(t_swap *s, uint64_t n);
uint64_t	rev_uint64(uint64_t n);
uint64_t	std_uint64(uint64_t n);

uint16_t	swap_uint16(t_swap *s, uint16_t n);
uint16_t	rev_uint16(uint16_t n);
uint16_t	std_uint16(uint16_t n);

#endif

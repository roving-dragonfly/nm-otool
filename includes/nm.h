/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:26 by aalves            #+#    #+#             */
/*   Updated: 2019/02/08 19:31:18 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

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

//to remove
# define T_STATIC_MAGIC 0x213C617263683E0A
# define T_STATIC_CIGAM 0X0A3E686372613C21

# define T_NM_FLAGS "gpr"
# define T_EXTERNAL_FLAG	0x0000000000000001
# define T_NOSORT_FLAG		0x0000000000000002
# define T_REVERSESORT_FLAG	0x0000000000000004

struct	s_proc_infos
{
	uint64_t		flags;
	uint64_t		n_files;
	char			**files;

};
typedef	struct s_proc_infos t_proc_infos;

struct	s_binfile
{
	char					*filename;
    void					*start;
	void					*end;
	t_list					*sym_list;
	t_list					*seg_list;

};
typedef	struct s_binfile t_binfile;

struct	s_symbol
{
	uint64_t					is64;
	char						*name;
	struct symtab_command		*symtab;
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

struct	s_static_lib
{
	t_binfile					*file;
	struct s_swap				*s;
};
typedef	struct s_static_lib t_static_lib;


union	u_metadata
{
    t_macho						macho;
	t_fat						fat;
	t_static_lib				ar;
};

/*
** nm.c
*/
int				main(int argc, char **argv);
void			ft_nm(t_proc_infos *cmd, t_binfile *file);

/*
** parse_cl.c
*/
t_proc_infos   	*parse_cl(int argc, char **argv);

/*
** endianess.c
*/
void			set_system_endianess(t_proc_infos *cmd);

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
int				 parse_file(t_binfile *file, void *start);

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
int				explore_fat_archs(t_fat *meta);

/*
** extract_symbols.c
*/
int				extract_symbols(t_macho *meta);

/*
** parse_symtab.c
*/
int				parse_symtable(t_macho *meta, struct symtab_command *symtab);

/*
** populate_symtab.c
*/
int				populate_symlist(t_macho *meta, struct symtab_command *symtab);

/*
** parse_segments.c
*/
int				parse_segments(t_macho *meta);


/*
** parse_symbols_data.c
*/
int				parse_symbols_data(t_macho *meta);

/*
** parse_sections.c
*/
int				parse_sections(t_macho *meta, t_segment *seg);


/*
** sort_symlist.c
*/
void			sort_symlist(t_list *list);

/*
** print_symbols.c
*/
void			print_symbols(t_binfile *file);

/*
** print_type .c
*/
void			print_type(t_binfile *file, t_symbol *sym);

/*
** cleanup.c
*/
void			cleanup_binfile(t_binfile *file);
void			cleanup_macho(t_macho *meta);
void			cleanup_fat(t_fat *meta);

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

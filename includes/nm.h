/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:26 by aalves            #+#    #+#             */
/*   Updated: 2019/02/02 18:31:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <inttypes.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
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


# define T_NM_FLAGS "gpr"
# define T_EXTERNAL_FLAG	0x0000000000000001
# define T_NOSORT_FLAG		0x0000000000000002
# define T_REVERSESORT_FLAG	0x0000000000000004
struct	s_command
{
	uint64_t		flags;
	uint64_t		n_files;
	char			**files;

};
typedef	struct s_command t_command;//better naming would be proc_infos

struct	s_binfile
{
	char					*filename;
    void					*start;
	void					*end;

};
typedef	struct s_binfile t_binfile;

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
	void						**lc_tab; //table of load commands (all of it) but better to point to the location only one alloc
};
typedef	struct s_macho t_macho;

struct	s_fat
{
	t_binfile					*file;
	struct fat_header			hdr;
	uint64_t					is64;
	union u_arch
	{
		struct fat_arch			fat32;
		struct fat_arch_64		fat64;
	}							**arch; //table of arch ptrs
	struct s_swap				*s;
};
typedef struct s_fat t_fat;

union	u_metadata
{
    t_macho						macho;
	t_fat						fat;
};

/*
** nm.c
*/
int				main(int argc, char **argv);
void			ft_nm(t_command *cmd, t_binfile *file);
/*
** parse_cl.c
*/
t_command		*parse_cl(int argc, char **argv);

/*
** endianess.c
*/
void			set_system_endianess(t_command *cmd);

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
** parse_macho_header.c
*/
int				parse_macho_header(t_binfile *file, t_macho *metadata, void *start);

/*
** parse_load_commands.c
*/
int				parse_load_commands(t_macho *meta);

/*
** cleanup.c
*/
void			cleanup_macho(t_macho *meta);

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

#endif

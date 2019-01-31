/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:26 by aalves            #+#    #+#             */
/*   Updated: 2019/02/01 00:13:51 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <inttypes.h>
# include <sys/mman.h>
//# include <mach-o/loader.h>
//# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

# define T_OPEN_FAILED 1
# define T_CLOSE_FAILED 2
# define T_FSTAT_FAILED 3
# define T_MMAP_FAILED 4
# define T_MUNMAP_FAILED 5


# define T_NM_FLAGS "gpr"
struct	s_command
{
	uint64_t	flags;
	uint64_t	n_files;
	char		**files;
};
typedef	struct s_command t_command;

struct	s_binfile
{
	char	*filename;
    void	*start;
	void	*end;
};
typedef	struct s_binfile t_binfile;


/*
** nm.c
*/
int	main(int argc, char **argv);

/*
** parse_cl.c
*/
t_command	*parse_cl(int argc, char **argv);

/*
** file_handling.c
*/
int		open_file(char *filename);
int		close_file(t_binfile *file, int fd);

/*
** file_mapping.c
*/
void	*map_file(t_binfile *file, int fd);
int		unmap_file(t_binfile *file);


uint8_t	endianess(void);


#endif

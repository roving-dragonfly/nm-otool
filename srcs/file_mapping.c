/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:00 by aalves            #+#    #+#             */
/*   Updated: 2019/01/31 22:06:25 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	*map_file(t_binfile *file, int fd)
{
	struct stat	stats;
	size_t		size;
	void		*p;

    if (fstat(fd, &stats) == -1)
	{
		ft_error(2, (char*[]){"fstat : ", file->file}, T_FSTAT_FAILED);
        return (NULL);
	}
	size = stats.st_size + stats.st_size % 4096;
	if ((p = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_error(2, (char*[]){"mmap :", file->file}, T_MMAP_FAILED);
		return (NULL);
	}
	file->start = p;
	file->end = (void*)((size_t)p + size);
	return (p);
}

void	unmap_file(t_binfile *file)
{
	if (munmap(file->start, (size_t)file->end - (size_t)file->start))
		ft_error_exit(2, (char*[]){"munmap : ", file->file}, T_MUNMAP_FAILED);
}

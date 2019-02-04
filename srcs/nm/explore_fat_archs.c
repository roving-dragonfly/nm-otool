/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_fat_archs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:51:03 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 16:16:21 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_fat *meta, void *p, union u_arch *arch)
{
	size_t	size;

	if (meta->file->end < p - sizeof arch)
	{
		ft_error(2, (char*[]){"fat_arch corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	size = meta->is64 ? swap_uint64(meta->s, arch->fat64.size) :
						swap_uint32(meta->s, arch->fat32.size);
	if (meta->file->end < p + size)
	{
		ft_error(2, (char*[]){"fat_arch corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int	explore_fat_archs(t_fat *meta)
{
	union u_arch	*arch;
	t_binfile		file;
	size_t			i;

    i = 0;
    while (i < meta->hdr.nfat_arch)
	{
		printf("\nParsing %lu\n", i);
		arch = meta->is64 ?
			meta->file->start +
			swap_uint64(meta->s, meta->arch[i]->fat64.offset) :
			meta->file->start +
			swap_uint32(meta->s, meta->arch[i]->fat32.offset);
		if (incongruent_ptr(meta, arch, meta->arch[i]))
			return (0);
		// Future me remember this shiet if you change t_binfile struct !!
		file.start = (void*)arch;
		file.end = (void*)arch + (meta->is64 ?
				  swap_uint64(meta->s, meta->arch[i]->fat64.size) :
				  swap_uint32(meta->s, meta->arch[i]->fat32.size));
		file.filename = meta->file->filename;
		if (!parse_file(&file, arch))
			return (0);
		i++;
	}
	return (1);
}

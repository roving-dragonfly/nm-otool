/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fat_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:55:23 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:28:34 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	set_fat_metadata(t_fat *meta, void *start)
{
	struct fat_header	*hdr;

	hdr = (struct fat_header*)start;
	meta->hdr.magic = swap_uint32(meta->s, hdr->magic);
	meta->hdr.nfat_arch = swap_uint32(meta->s, hdr->nfat_arch);
	meta->arch_start = start + sizeof(struct fat_header);
}

int	parse_fat_header(t_binfile *file, t_fat *metadata, void *start)
{
	uint32_t	magic;

	if (start > file->end - sizeof(struct fat_header))
		return (0);
	metadata->file = file;
	magic = *(uint32_t*)start;
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		metadata->is64 = 0;
    else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		metadata->is64 = 1;
	else
		return (0);
	metadata->s = (magic == FAT_MAGIC_64 || magic == FAT_MAGIC) ?
		noswap_tab() : swap_tab();
	set_fat_metadata(metadata, start);

	return(1);
}

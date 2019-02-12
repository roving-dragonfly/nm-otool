/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_macho_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:30:05 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 00:06:28 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	set_macho_header(t_macho *meta, void *start)
{
    struct mach_header_64 *hdr;

	hdr = (struct mach_header_64*)start;
	meta->hdr.hdr64.magic = swap_uint32(meta->s, hdr->magic);
	meta->hdr.hdr64.cputype = swap_uint32(meta->s, hdr->cputype);
	meta->hdr.hdr64.cpusubtype = swap_uint32(meta->s, hdr->cpusubtype);
	meta->hdr.hdr64.filetype = swap_uint32(meta->s, hdr->filetype);
    meta->hdr.hdr64.ncmds = swap_uint32(meta->s, hdr->ncmds);
    meta->hdr.hdr64.sizeofcmds = swap_uint32(meta->s, hdr->sizeofcmds);
	meta->hdr.hdr64.flags = swap_uint32(meta->s, hdr->flags);
	if (meta->is64)
	{
		meta->hdr.hdr64.reserved = swap_uint32(meta->s, hdr->reserved);
        meta->lc_start = start + sizeof(struct mach_header_64);
	}
	else
		meta->lc_start = start + sizeof(struct mach_header);
}

int	parse_macho_header(t_binfile *file, t_macho *metadata, void *start)
{
	uint32_t	magic;

	if (start > file->end - sizeof(struct mach_header_64))
		return (0);
	metadata->file = file;
	magic = *(uint32_t*)start;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		metadata->is64 = 0;
    else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		metadata->is64 = 1;
	else
		return (0);
	metadata->s = (magic == MH_MAGIC || magic == MH_MAGIC_64) ?
		noswap_tab(): swap_tab();
	set_macho_header(metadata, start);
	return(1);
}

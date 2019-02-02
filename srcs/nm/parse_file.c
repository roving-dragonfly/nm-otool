/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:04 by aalves            #+#    #+#             */
/*   Updated: 2019/02/02 18:56:11 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void print_macho_header(t_macho *meta)
{
	if (meta->is64)
	{
		printf("Header 64 :\n");
		printf("Magic : %x\n", meta->hdr.hdr64.magic);
		printf("cputype : %x\n", meta->hdr.hdr64.cputype);
		printf("cpusubtype : %x\n", meta->hdr.hdr64.cpusubtype);
		printf("filetype : %x\n", meta->hdr.hdr64.filetype);
		printf("ncmds : %x\n", meta->hdr.hdr64.ncmds);
		printf("sizeofcmds : %x\n", meta->hdr.hdr64.sizeofcmds);
		printf("flags : %x\n", meta->hdr.hdr64.flags);
		printf("reserved : %x\n", meta->hdr.hdr64.reserved);
	}
	else
	{
		printf("Header 32 :\n");
		printf("Magic : %x\n", meta->hdr.hdr32.magic);
		printf("cputype : %x\n", meta->hdr.hdr32.cputype);
		printf("cpusubtype : %x\n", meta->hdr.hdr32.cpusubtype);
		printf("filetype : %x\n", meta->hdr.hdr32.filetype);
		printf("ncmds : %x\n", meta->hdr.hdr32.ncmds);
		printf("sizeofcmds : %x\n", meta->hdr.hdr32.sizeofcmds);
		printf("flags : %x\n", meta->hdr.hdr32.flags);
	}
}

static void	print_lc_tab(t_macho *meta)
{
	size_t i = 0;
	struct load_command *lc;

	while (meta->lc_tab[i])
	{
		lc = meta->lc_tab[i];
		printf("Load command : %.16llx\tsize %.16llx\n", swap_uint64(meta->s, lc->cmd), swap_uint64(meta->s, lc->cmdsize));
		i++;
	}
}

/*
** Recursively parses file by format, populating symbol table on the way
*/
int parse_file(t_binfile *file, void *start)
{
	union u_metadata	meta;

	ft_bzero(&meta, sizeof(meta));
	printf("Parsing %p\n", start);
	if (parse_fat_header(file, &meta.fat, start))
	{
        parse_fat_arch(&meta.fat);
		//foreach arch parse_file
	}
	else if (parse_macho_header(file, &meta.macho, start))
	{
		print_macho_header(&meta.macho);
		if (!parse_load_commands(&meta.macho))
			return (0);
		print_lc_tab(&meta.macho);
		//populate symtable
        cleanup_macho(&meta.macho);
	}
	else
	{
		ft_error(2, (char*[]){"Unrecognized format : ", file->filename},
				T_PARSING_FAILED);
		return (0);
	}
	return (1);
}

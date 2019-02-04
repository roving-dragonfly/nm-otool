/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:04 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 18:50:27 by aalves           ###   ########.fr       */
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
		printf("Load command : %.8x\tsize %.8x\n", swap_uint32(meta->s, lc->cmd), swap_uint32(meta->s, lc->cmdsize));
		i++;
	}
}

static void print_fat_header(t_fat *meta)
{
    if (meta->is64)
        printf("Fat Header 64 :\n");
	else
		printf("Fat Header 32 :\n");

	printf("Magic : %x \nnfat_arch : %x\n", meta->hdr.magic, meta->hdr.nfat_arch);
}

static void print_fat_arch(t_fat *meta)
{
	size_t i = 0;

	while (meta->arch[i])
	{
		printf("\nfat_arch %lu\n", i);
        printf("cputype : %x\n", swap_uint32(meta->s, meta->arch[i]->fat32.cputype));
        printf("cpusubtype : %x\n", swap_uint32(meta->s, meta->arch[i]->fat32.cpusubtype));
		if (meta->is64)
		{
            printf("offset : %llu\n", swap_uint64(meta->s, meta->arch[i]->fat64.offset));
            printf("size : %llu\n", swap_uint64(meta->s, meta->arch[i]->fat64.size));
            printf("align : %ld\n", ft_pow(2, swap_uint32(meta->s, meta->arch[i]->fat64.align)));
			printf("reserved : %x\n", swap_uint32(meta->s, meta->arch[i]->fat64.reserved));
		}
		else
		{
			printf("offset : %u\n", swap_uint32(meta->s, meta->arch[i]->fat32.offset));
			printf("size : %u\n", swap_uint32(meta->s, meta->arch[i]->fat32.size));
			printf("align : %ld\n", ft_pow(2, swap_uint32(meta->s, meta->arch[i]->fat32.align)));
		}
		i++;
	}
}

static void print_symbol(t_list *sym_link)
{
	t_symbol *sym = (t_symbol*)sym_link->content;
	printf("Symbol:\n");
    if (sym->is64)
	{
		printf("n_strx : %.8x\n", sym->nlist.n64.n_un.n_strx);
        printf("n_type : %x\n", sym->nlist.n64.n_type);
		printf("n_sect : %x\n", sym->nlist.n64.n_sect);
        printf("n_desc : %.4x\n", sym->nlist.n64.n_desc);
		printf("n_value : %.16llx\n", sym->nlist.n64.n_value);
	}
	else
	{
		printf("n_strx : %.8x\n", sym->nlist.n32.n_un.n_strx);
		printf("n_type : %x\n", sym->nlist.n32.n_type);
		printf("n_sect : %x\n", sym->nlist.n32.n_sect);
		printf("n_desc : %.4x\n", sym->nlist.n32.n_desc);
		printf("n_value : %.8x\n", sym->nlist.n32.n_value);
	}
}

static void print_sym_tab(t_macho *meta)
{
    t_list *link;

	link = meta->sym_list;
	while (link)
	{
		print_symbol(link);
		link = link->next;
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
		//When dev is done regroup all this in a if (... || ...)
		print_fat_header(&meta.fat);
		if (!parse_fat_arch(&meta.fat))
			return (0);
		print_fat_arch(&meta.fat);
		if (!explore_fat_archs(&meta.fat))
			return (0);
		cleanup_fat(&meta.fat); //if 0 is returned still call this
	}
	else if (parse_macho_header(file, &meta.macho, start))
	{
		print_macho_header(&meta.macho);
		if (!parse_load_commands(&meta.macho))
			return (0);
		print_lc_tab(&meta.macho);
		if (!extract_symbols(&meta.macho))
			return (0);
		print_sym_tab(&meta.macho);
        cleanup_macho(&meta.macho); //if 0 is returned still call this
	}
	else
	{
		ft_error(2, (char*[]){"Unrecognized format : ", file->filename},
				T_PARSING_FAILED);
		return (0);
	}
	return (1);
}

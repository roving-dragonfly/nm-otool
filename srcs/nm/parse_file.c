/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:04 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 18:06:46 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


/* static void print_symbol(t_list *sym_link) */
/* { */
/* 	t_symbol *sym = (t_symbol*)sym_link->content; */
/* 	printf("Symbol:\n"); */
/*     if (sym->is64) */
/* 	{ */
/*         printf("NAME 64 : %s\n", sym->name); */
/* 		printf("n_strx : %.8x\n", sym->nlist.n64.n_un.n_strx); */
/*         printf("n_type : %x\n", sym->nlist.n64.n_type); */
/* 		printf("n_sect : %x\n", sym->nlist.n64.n_sect); */
/*         printf("n_desc : %.4x\n", sym->nlist.n64.n_desc); */
/* 		printf("n_value : %.16llx\n", sym->nlist.n64.n_value); */
/* 	} */
/* 	else */
/* 	{ */
/* 		printf("NAME 32 : %s\n", sym->name); */
/* 		printf("n_strx : %.8x\n", sym->nlist.n32.n_un.n_strx); */
/* 		printf("n_type : %x\n", sym->nlist.n32.n_type); */
/* 		printf("n_sect : %x\n", sym->nlist.n32.n_sect); */
/* 		printf("n_desc : %.4x\n", sym->nlist.n32.n_desc); */
/* 		printf("n_value : %.8x\n", sym->nlist.n32.n_value); */
/* 	} */
/* } */

/* static void print_sym_tab(t_binfile *file) */
/* { */
/*     t_list *link; */

/* 	link = file->sym_list; */
/* 	printf("\n~~~~~Printing symtable~~~~~~~\n"); */
/* 	while (link) */
/* 	{ */
/* 		print_symbol(link); */
/* 		link = link->next; */
/* 	} */
/* } */


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

static void print_sections(t_segment *seg)
{
    size_t	i = 0;

	while (seg->sect_tab && seg->sect_tab[i])
	{
		printf("Sectname : %s\n", ((struct section*)seg->sect_tab[i])->sectname);
		printf("Segname : %s\n", ((struct section*)seg->sect_tab[i])->segname);
		i++;
	}
}

static void print_seglist(t_macho *meta)
{
	t_list *link = meta->seg_list;
	t_segment *seg;

	while (link->next)
		link = link->next;

	while (link)
	{
		seg = link->content;
		if (seg->is64)
		{
			printf("\nSegment 64\n");
			printf("name : %s\n", seg->seg.s64.segname);
			printf("vmaddr : %llx\n", seg->seg.s64.vmaddr);
            printf("vmsize : %llx\n",  seg->seg.s64.vmsize);
            printf("fileoff : %llx\n",  seg->seg.s64.fileoff);
            printf("filesize : %llx\n", seg->seg.s64.filesize);
			printf("maxprot : %x\n", seg->seg.s64.maxprot);
			printf("initprot : %x\n", seg->seg.s64.initprot);
			printf("nsects : %x\n", seg->seg.s64.nsects);
			printf("flags : %x\n", seg->seg.s64.flags);
		}
		else
		{
			printf("\nSegment 32\n");
			printf("name : %s\n", seg->seg.s32.segname);
			printf("vmaddr : %x\n", seg->seg.s32.vmaddr);
            printf("vmsize : %x\n",  seg->seg.s32.vmsize);
            printf("fileoff : %x\n",  seg->seg.s32.fileoff);
            printf("filesize : %x\n", seg->seg.s32.filesize);
			printf("maxprot : %x\n", seg->seg.s32.maxprot);
			printf("initprot : %x\n", seg->seg.s32.initprot);
            printf("nsects : %x\n", seg->seg.s32.nsects);
			printf("flags : %x\n", seg->seg.s32.flags);
		}
		print_sections(seg);
		link = link->prev;
	}
}

/*
** Recursively parses file by format, populating symbol table on the way
*/
int parse_file(t_binfile *file, void *start)
{
	union u_metadata	meta;

	ft_bzero(&meta, sizeof(union u_metadata));
	if (parse_fat_header(file, &meta.fat, start))
	{
		if (!parse_fat_arch(&meta.fat) || !explore_fat_archs(&meta.fat))
		{
            cleanup_fat(&meta.fat);
			return (0);
 		}
		cleanup_fat(&meta.fat);
	}
	else if (parse_macho_header(file, &meta.macho, start))
	{
		if (!parse_load_commands(&meta.macho) || !extract_symbols(&meta.macho) ||
			!parse_segments(&meta.macho) || !parse_symbols_data(&meta.macho))
		{
			cleanup_macho(&meta.macho);
			return (0);
		}
		cleanup_macho(&meta.macho);
	}
	else if (parse_static_lib_header(file, &meta.ar, start))
	{
		if (!parse_symbol_table(&meta.ar) || !extract_static_symbols(&meta.ar))
		{
			cleanup_static(&meta.ar);
            return (0);
		}
	}
	else
	{
		ft_error(2, (char*[]){"Unrecognized format : ", file->filename},
				T_PARSING_FAILED);
		return (0);
	}
	return (1);
}

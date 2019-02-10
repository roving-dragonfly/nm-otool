/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:13:48 by aalves            #+#    #+#             */
/*   Updated: 2019/02/10 20:22:46 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_symbol(t_macho *meta, t_symbol *sym)
{
    	uint32_t	strx;

		strx = (sym->is64 ? sym->nlist.n64.n_un.n_strx :
				sym->nlist.n32.n_un.n_strx);
		if (meta->file->end < meta->file->start +
			swap_uint32(meta->s, sym->symtab->stroff) + strx ||
			strx > swap_uint32(meta->s, sym->symtab->strsize))
		{
            printf("strx = %x\n", strx);
			printf("stroff = %x\n", swap_uint32(meta->s, sym->symtab->stroff));
			printf("strsize = %x\n", swap_uint32(meta->s, sym->symtab->strsize));
			ft_error(2, (char*[]){"string table corrupt : ",
						meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static void *get_section(t_macho *meta, uint8_t n)
{
	t_list		*link;
	t_segment	*seg;

	link = meta->seg_list;
	while (link->next)
		link = link->next;
	while (link)
	{
		seg = link->content;
		if (n <= (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects))
            break;
		n -= (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects);
		link = link->prev;
	}
	if (!link && (n > (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects)))
	{
		ft_error(2, (char*[]){"symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (NULL);
	}
	return (seg->sect_tab[n - 1]);
}


static int	save_symbol_sect(t_macho *meta, t_symbol *sym)
{
	uint8_t	n_sect;

	n_sect = (sym->is64 ? sym->nlist.n64.n_sect : sym->nlist.n32.n_sect);
	if (((sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type) & N_TYPE) != N_SECT)
		return (1);
	if (n_sect == 0)
	{
		ft_error(2, (char*[]){"symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (0);
	}
	if (!(sym->section = get_section(meta, n_sect)))
		return (0);
	return (1);
}

static int	save_symbol_string(t_macho *meta, t_symbol *sym)
{
	uint32_t	strx;
	size_t		i;

	strx = (sym->is64 ? sym->nlist.n64.n_un.n_strx :
			sym->nlist.n32.n_un.n_strx);
	sym->name = meta->file->start +	swap_uint32(meta->s, sym->symtab->stroff) + strx;
	if (!sym->name)
		return (1);
	i = 0;
	while (sym->name[i])
	{
		if (meta->file->end < (void*)(sym->name + i))
		{
			ft_error(2, (char*[]){"symbol name table corrupt : ",
						meta->file->filename}, T_CORRUPT_FILE);
			return (0);
		}
		i++;
	}
	return (1);
}

static void print_symbol(t_list *sym_link)
{
	t_symbol *sym = (t_symbol*)sym_link->content;
	printf("Symbol:\n");
    if (sym->is64)
	{
//        printf("NAME 64 : %s\n", sym->name);
        printf("64\n");
		printf("n_strx : %.8x\n", sym->nlist.n64.n_un.n_strx);
        printf("n_type : %x\n", sym->nlist.n64.n_type);
		printf("n_sect : %x\n", sym->nlist.n64.n_sect);
        printf("n_desc : %.4x\n", sym->nlist.n64.n_desc);
		printf("n_value : %.16llx\n", sym->nlist.n64.n_value);
	}
	else
	{

//		printf("NAME 32 : %s\n", sym->name);
		printf("32\n");
		printf("n_strx : %.8x\n", sym->nlist.n32.n_un.n_strx);
		printf("n_type : %x\n", sym->nlist.n32.n_type);
		printf("n_sect : %x\n", sym->nlist.n32.n_sect);
		printf("n_desc : %.4x\n", sym->nlist.n32.n_desc);
		printf("n_value : %.8x\n", sym->nlist.n32.n_value);
	}
}

int	parse_symbols_data(t_macho *meta)
{
	t_list		*link;

	link = meta->file->sym_list;
	while (link)
	{
        if (((t_symbol*)link->content)->arch.type != meta->hdr.hdr32.cputype ||
			((t_symbol*)link->content)->arch.sub != meta->hdr.hdr32.cpusubtype)
		{
			link = link->next;
			continue;
		}
		if (incongruent_symbol(meta, link->content) ||
			!save_symbol_string(meta, link->content) ||
 			!save_symbol_sect(meta, link->content))
			return (0);
		link = link->next;
	}
	return (1);
}

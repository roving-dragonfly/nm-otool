/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:21:59 by aalves            #+#    #+#             */
/*   Updated: 2019/02/15 11:55:54 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	put_arch_name(cpu_type_t arch)
{
    ft_putstr(" (architecture ");
	if (arch == CPU_TYPE_VAX)
		ft_putstr("vax");
    else if (arch == CPU_TYPE_MC680x0)
		ft_putstr("mc680x0");
	else if (arch == CPU_TYPE_X86)
		ft_putstr("i386");
	else if (arch == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (arch == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else if (arch == CPU_TYPE_HPPA)
		ft_putstr("hppa");
	else if (arch == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (arch == CPU_TYPE_ARM64)
		ft_putstr("arm64");
	else if (arch == CPU_TYPE_MC88000)
		ft_putstr("mc88000");
	else if (arch == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (arch == CPU_TYPE_I860)
		ft_putstr("i860");
	else if (arch == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (arch == CPU_TYPE_POWERPC64)
		ft_putstr("ppc64");
	ft_putchar(')');
}

static void	print_addr(t_macho *meta, size_t pos)
{
	size_t	i;

	if (meta->is64)
	{
		i = 16;
        while (i-- > ft_strlen(ft_static_ulltoa_base((size_t)pos, "0123456789abcdef")))
			ft_putchar('0');
		ft_putstr(ft_static_ulltoa_base(pos, "0123456789abcdef"));
	}
	else
	{
		i = 8;
        while (i-- > ft_strlen(ft_static_ulltoa_base((size_t)pos, "0123456789abcdef")))
			ft_putchar('0');
		ft_putstr(ft_static_ulltoa_base(pos, "0123456789abcdef"));
	}
}

static void print_hexcode(t_macho *meta, uint8_t *pos, size_t n)
{
    uint8_t	c;

	if (meta->hdr.hdr32.cputype == CPU_TYPE_POWERPC)
	{
		while (n)
		{
			c = *pos;
			ft_putchar(((c & 0xF0) >> 4 > 9 ? ((c & 0xF0) >> 4) + 'a' - 10 : ((c & 0xF0) >> 4) + '0'));
			ft_putchar(((c & 0x0F) > 9 ? (c & 0x0F) + 'a' - 10 : (c & 0x0F) + '0'));
			if (!((n - 1) % 4))
				ft_putchar(' ');
			pos++;
			n--;
		}
	}
	else
	{
		while (n)
		{
			c = *pos;
			ft_putchar(((c & 0xF0) >> 4 > 9 ? ((c & 0xF0) >> 4) + 'a' - 10 : ((c & 0xF0) >> 4) + '0'));
			ft_putchar(((c & 0x0F) > 9 ? (c & 0x0F) + 'a' - 10 : (c & 0x0F) + '0'));
			ft_putchar(' ');
			pos++;
			n--;
		}

	}
}

static void	print_obj_name(char *name)
{
    ft_putstr("(");
	ft_putstr(name);
	ft_putstr(")");
}

static void	print_section(t_macho *meta, void *sect, t_segment *seg)
{
    uint64_t	pos;
	uint64_t	size;

	ft_putstr(meta->file->filename);
	if (meta->file->multi_arch)
        put_arch_name(meta->hdr.hdr32.cputype);
	if (meta->file->obj)
        print_obj_name(meta->file->obj);
	ft_putstr(":\nContents of (__TEXT,__text) section\n");
	size = meta->is64 ? swap_uint64(meta->s, ((struct section_64*)sect)->size) : swap_uint32(meta->s, ((struct section*)sect)->size);
	pos = 0;
	while (pos < size && meta->file->start + pos + 0x10 < meta->file->end)
	{
		print_addr(meta, (meta->is64 ? swap_uint64(meta->s, ((struct section_64*)sect)->offset) :
				   swap_uint32(meta->s, ((struct section*)sect)->offset)) + pos +
				   (seg->is64 ? seg->seg.s64.vmaddr - seg->seg.s64.fileoff : seg->seg.s32.vmaddr - seg->seg.s32.fileoff));
		ft_putstr("\t");
		print_hexcode(meta, meta->file->start + (meta->is64 ? swap_uint64(meta->s, ((struct section_64*)sect)->offset) :
										  swap_uint32(meta->s, ((struct section*)sect)->offset)) + pos, (size - pos) > 0x10 ? 0x10 : (size - pos));
		ft_putstr("\n");
		pos += 0x10;
	}
}


void		print_text_segment(t_macho *meta)
{
    t_list		*link;
	t_segment	*seg;
	size_t		i;

    link = meta->seg_list;
	while (link->next)
		link = link->next;
	while (link)
	{
		i = 0;
		seg = link->content;
		while (i < (meta->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects))
		{
			if (!ft_strcmp("__text", ((struct section*)seg->sect_tab[i])->sectname)
				&& (!meta->file->arch ||
					(meta->file->arch->type == meta->hdr.hdr32.cputype &&
					 meta->file->arch->sub == meta->hdr.hdr32.cpusubtype)))
				print_section(meta, seg->sect_tab[i], seg);
			i++;
		}
		link = link->prev;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:21:59 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 07:26:00 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

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

static void print_hexcode(uint8_t *pos, size_t n)
{
    uint8_t	c;

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

static void	print_section(t_macho *meta, void *sect, t_segment *seg)
{
    uint64_t	pos;

	uint64_t	size;

	ft_putstr(meta->file->filename);
	ft_putstr(":\nContents of (__TEXT,__text) section\n");
	size = meta->is64 ? ((struct section_64*)sect)->size : ((struct section*)sect)->size;
	pos = 0;
	while (pos < size && meta->file->start + pos + 0x10 < meta->file->end)
	{
		print_addr(meta, (meta->is64 ?((struct section_64*)sect)->offset :
						  ((struct section*)sect)->offset) + pos + (seg->is64 ? seg->seg.s64.vmaddr : seg->seg.s32.vmaddr));
		ft_putstr("\t");
		print_hexcode(meta->file->start + (meta->is64 ?((struct section_64*)sect)->offset :
										   ((struct section*)sect)->offset) + pos, (size - pos) > 0x10 ? 0x10 : (size - pos));
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
			if (!ft_strncmp("__text", ((struct section*)seg->sect_tab[i])->sectname, 6)
				&& (!meta->file->arch ||
					(meta->file->arch->type == meta->hdr.hdr32.cputype &&
					 meta->file->arch->sub == meta->hdr.hdr32.cpusubtype)))
				print_section(meta, seg->sect_tab[i], seg);
			i++;
		}
		link = link->prev;
	}

}

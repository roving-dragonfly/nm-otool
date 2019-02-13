/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_macho_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 02:55:38 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 05:17:32 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	print_header1(t_macho *meta)
{
	size_t	i;

	ft_putstr("Mach header\n");
	ft_putstr("      magic cputype cpusubtype  caps    filetype ncmds ");
	ft_putstr("sizeofcmds      flags\n  0x");
    ft_putstr(ft_static_ulltoa_base(meta->hdr.hdr32.magic, "0123456789abcdef"));
	ft_putstr(" ");
	ft_putstr(ft_static_ulltoa(meta->hdr.hdr32.cputype));
    i = 10;
	while (i-- > ft_strlen(ft_static_ulltoa(meta->hdr.hdr32.cpusubtype & ~CPU_SUBTYPE_MASK)))
		ft_putchar(' ');
	ft_putstr(ft_static_ulltoa(meta->hdr.hdr32.cpusubtype & ~CPU_SUBTYPE_MASK));
    ft_putstr("  0x");
	ft_putstr(ft_static_ulltoa_base((meta->hdr.hdr32.cpusubtype &
									 CPU_SUBTYPE_MASK) >> 24, "0123456789abcdef"));
	i = 12;
	while (i-- > ft_strlen(ft_static_ulltoa(meta->hdr.hdr32.filetype)))
		ft_putchar(' ');
	ft_putstr(ft_static_ulltoa(meta->hdr.hdr32.filetype));
	i = 6;
	while (i-- > ft_strlen(ft_static_ulltoa(meta->hdr.hdr32.ncmds)))
		ft_putchar(' ');
	ft_putstr(ft_static_ulltoa(meta->hdr.hdr32.ncmds));
}

static void	print_header2(t_macho *meta)
{
	size_t	i;

	i = 11;
	while (i-- > ft_strlen(ft_static_ulltoa(meta->hdr.hdr32.sizeofcmds)))
		ft_putchar(' ');
	ft_putstr(ft_static_ulltoa(meta->hdr.hdr32.sizeofcmds));
	ft_putstr(" 0x");
	i = 8;
	while (i-- > ft_strlen(ft_static_ulltoa_base(meta->hdr.hdr32.flags, "0123456789abcdef")))
		ft_putchar('0');
	ft_putstr(ft_static_ulltoa_base(meta->hdr.hdr32.flags, "0123456789abcdef"));
	ft_putstr("\n");

}

void	print_macho_header(t_macho *meta)
{
	if (!meta->file->arch || (meta->file->arch->type == meta->hdr.hdr32.cputype &&
							  meta->file->arch->sub == meta->hdr.hdr64.cpusubtype))
	{
		print_header1(meta);
		print_header2(meta);
	}
}

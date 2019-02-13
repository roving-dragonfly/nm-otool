/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fat_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 02:06:24 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 05:04:06 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	print_fat_arch(t_fat *meta, union u_arch *arch)
{
	ft_putstr("    cputype ");
	ft_putstr(ft_static_ulltoa(swap_uint32(meta->s, meta->is64 ? arch->fat64.cputype : arch->fat32.cputype)));
    ft_putstr("\n    cpusubtype ");
    ft_putstr(ft_static_ulltoa(swap_uint32(meta->s, meta->is64 ?
		arch->fat64.cpusubtype : arch->fat32.cpusubtype) & ~CPU_SUBTYPE_MASK));
    ft_putstr("\n    capabilities 0x");
	ft_putstr(ft_static_ulltoa_base((swap_uint32(meta->s, (meta->is64 ?
		arch->fat64.cpusubtype : arch->fat32.cpusubtype)) &
		CPU_SUBTYPE_MASK) >> 24, "0123456789abcdef"));
	ft_putstr("\n    offset ");
    ft_putstr(ft_static_ulltoa(meta->is64 ? swap_uint64(meta->s, arch->fat64.offset) :
							   swap_uint32(meta->s, arch->fat32.offset)));
    ft_putstr("\n    size ");
	ft_putstr(ft_static_ulltoa(meta->is64 ? swap_uint64(meta->s, arch->fat64.size) :
				  swap_uint32(meta->s, arch->fat32.size)));
	ft_putstr("\n    align 2^");
    ft_putstr(ft_static_ulltoa(swap_uint32(meta->s, (meta->is64 ? arch->fat64.align :
								arch->fat32.align))));
	ft_putstr(" (");
	ft_putstr(ft_static_ulltoa(ft_pow(2, swap_uint32(meta->s,
		 (meta->is64 ? arch->fat64.align : arch->fat32.align)))));
	ft_putstr(")");
}

void	print_fat_header(t_proc_infos *pi, t_fat *meta)
{
	size_t	i;

    ft_putstr("Fat headers\n");
	ft_putstr("Fat magic 0x");
	ft_putstr(ft_static_ulltoa_base(meta->hdr.magic, "0123456789abcdef"));
	ft_putstr("\nfat_arch ");
	ft_putstr(ft_static_ulltoa(meta->hdr.nfat_arch));
	i = 0;
	while (i < meta->hdr.nfat_arch)
	{
		ft_putstr("\narchitecture ");
		ft_putstr(ft_static_ulltoa(i));
		ft_putstr("\n");
		print_fat_arch(meta, meta->arch[i]);
		i++;
	}
	ft_putstr("\n");
}

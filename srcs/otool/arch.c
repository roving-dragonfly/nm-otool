/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 03:39:28 by aalves            #+#    #+#             */
/*   Updated: 2019/02/14 18:09:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

/*
** Done this way to have the same output for crappy macho, like sqlite3
*/
void				get_default_arch(t_fat *meta)
{
	size_t			i;
	static t_arch	arch;

	i = 0;
	ft_bzero(&arch, sizeof(arch));
	while (meta->arch[i])
	{
		if (swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cputype : meta->arch[i]->fat32.cputype)) == CPU_TYPE_X86_64)
		{
			arch.type = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cputype : meta->arch[i]->fat32.cputype));
			arch.sub = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cpusubtype : meta->arch[i]->fat32.cpusubtype));
			meta->file->multi_arch = 0;
			meta->file->arch = &arch;
			return ;
		}
		i++;
	}
    meta->file->arch = NULL;
	meta->file->multi_arch = 1;
}

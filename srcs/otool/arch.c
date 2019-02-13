/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 03:39:28 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 04:44:22 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

/* static int		arch_in_tab(struct s_arch *tab, struct s_arch arch) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	while (tab[i].type) */
/* 	{ */
/* 		if (tab[i].type == arch.type && */
/* 			tab[i].sub == arch.sub) */
/* 			return (-1); */
/* 		i++; */
/* 	} */
/* 	return (i); */
/* } */

/* static struct s_arch	*get_arch_tab(t_fat *meta) */
/* { */
/* 	static struct s_arch	arch_tab[32]; */
/*     t_arch		arch; */
/* 	size_t		i; */

/* 	if (arch_tab[0].type) */
/* 		return (arch_tab); */
/* 	i = 0; */
/* 	while (meta->arch[i]) */
/* 	{ */
/* 		arch.type = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cputype : meta->arch[i]->fat32.cputype)); */
/* 		arch.sub = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cpusubtype : meta->arch[i]->fat32.cpusubtype)); */
/* 		i++; */
/* 	} */
/* 	return (arch_tab); */
/* } */

void				get_default_arch(t_fat *meta)
{
	size_t			i;
	static t_arch	arch;

	i = 0;
	while (meta->arch[i])
	{
		if (swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cputype : meta->arch[i]->fat32.cputype)) == CPU_TYPE_X86_64)
		{
			arch.type = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cputype : meta->arch[i]->fat32.cputype));
			arch.sub = swap_uint32(meta->s, (meta->is64 ? meta->arch[i]->fat64.cpusubtype : meta->arch[i]->fat32.cpusubtype));
		}
		i++;
	}
	//May backfire on archs where no default on std otool
	meta->file->arch = &arch;
}

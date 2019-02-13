/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fat_arch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:41:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 04:57:17 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	incongruent_ptr(t_fat *meta, void *p)
{
	size_t	arch_size;

    arch_size = meta->is64 ? sizeof(struct fat_arch_64) : sizeof(struct fat_arch);
	if (p < meta->arch_start || p > meta->file->end ||
		p > meta->arch_start + arch_size * (meta->hdr.nfat_arch - 1))
	{
        ft_error(2, (char*[]){"fat_arch corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_fat *meta, void *p)
{
	size_t	arch_size;

    arch_size = meta->is64 ? sizeof(struct fat_arch_64) : sizeof(struct fat_arch);
	if (p != meta->arch_start + arch_size * meta->hdr.nfat_arch)
	{
		ft_error(2, (char*[]){"fat_arch wrong offset : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	bad_alignement(t_fat *meta, union u_arch *arch)
{
	if (meta->is64 && swap_uint32(meta->s, arch->fat64.offset) % ft_pow(2, swap_uint32(meta->s, arch->fat64.align)))
	{
		ft_error(2, (char*[]){"fat_arch not aligned : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	else if (swap_uint32(meta->s, arch->fat32.offset) % ft_pow(2, swap_uint32(meta->s, arch->fat32.align)))
	{
		ft_error(2, (char*[]){"fat_arch not aligned : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static void	**populate_fat_arch(t_fat *meta)
{
	size_t	i;
	void	*ptr;
	void	**arch_tab;

	i = 0;
	ptr = meta->arch_start;
	if (!(arch_tab = ft_memalloc(sizeof(void*) * (meta->hdr.nfat_arch + 1))))
		return (NULL);
	while (i < meta->hdr.nfat_arch)
	{
		arch_tab[i] = ptr;
		if (meta->is64)
			ptr += sizeof(struct fat_arch_64);
        else
			ptr += sizeof(struct fat_arch);
		i++;
	}
	arch_tab[i] = NULL;
	return (arch_tab);
}

/*
** Fat arch parsing, done in 2 pass
** First checking for corruption then storing them in table
*/
int	parse_fat_arch(t_fat *meta)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = meta->arch_start;
	while (i < meta->hdr.nfat_arch)
	{
		if (incongruent_ptr(meta, ptr) ||
			bad_alignement(meta, ptr))
			return (0);
		if (meta->is64)
			ptr += sizeof(struct fat_arch_64);
        else
			ptr += sizeof(struct fat_arch);
		i++;
	}
    if (incongruent_size(meta, ptr))
		return (0);
	if (!(meta->arch = (union u_arch **)populate_fat_arch(meta)))
		return (0);
	get_default_arch(meta);
	return (1);
}

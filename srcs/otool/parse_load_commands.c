/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_load_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 12:55:14 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 04:44:25 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	incongruent_ptr(t_macho *meta, void *p)
{
	if (p < meta->lc_start ||
		p > meta->lc_start + meta->hdr.hdr32.sizeofcmds
		- sizeof(struct load_command) ||
		p > meta->file->end)
	{
		ft_error(2, (char*[]){"load command corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_macho *meta, size_t offset)
{
	if (offset != meta->hdr.hdr32.sizeofcmds)
	{
		ft_error(2, (char*[]){"load command wrong offset : "}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	bad_alignement(t_macho *meta, void *p)
{
	size_t mod;

	mod = meta->is64 ? 8 : 4;
	if ((size_t)p % mod)
	{
		ft_error(2, (char*[]){"load command unaligned : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static void		**populate_lc_tab(t_macho *meta)
{
    size_t				offset;
	size_t				i;
	struct load_command	*pt_lc;
	void				**lc_tab;

	offset = 0;
	i = 0;
	if (!(lc_tab = ft_memalloc(sizeof(void*) * (meta->hdr.hdr32.ncmds + 1))))
	{
		ft_error(2, (char*[]){"malloc failed : ", meta->file->filename}, 0);
		return (NULL);
	}
	while (i < meta->hdr.hdr32.ncmds)
	{
		pt_lc = (struct load_command*)(meta->lc_start + offset);
		lc_tab[i] = pt_lc;
		i++;
		offset += swap_uint32(meta->s, pt_lc->cmdsize);
	}
	lc_tab[i] = NULL;
	return (lc_tab);
}

/*
** Load commands parsing, done in 2 pass
** First checking for corruption then storing them in table
*/
int	parse_load_commands(t_macho *meta)
{
    size_t				offset;
	size_t				i;
	struct load_command	*pt_lc;

 	offset = 0;
	i = 0;
	while (i < meta->hdr.hdr32.ncmds)
	{
		pt_lc = (struct load_command*)(meta->lc_start + offset);
		if (incongruent_ptr(meta, (void*)pt_lc) ||
			bad_alignement(meta, (void*)pt_lc))
			return (0);
		offset += swap_uint32(meta->s, pt_lc->cmdsize);
		i++;
	}
	if (incongruent_size(meta, offset))
		return (0);
	if (!(meta->lc_tab = populate_lc_tab(meta)))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:33:11 by aalves            #+#    #+#             */
/*   Updated: 2019/02/06 14:42:21 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_macho *meta, struct symtab_command *symtab,
							void *p)
{
	size_t	nlist_size;

	nlist_size = meta->is64 ? sizeof(struct nlist_64) : sizeof(struct nlist);
	if (p > meta->file->end ||
		p > meta->file->start + swap_uint32(meta->s, symtab->symoff)
		+ (swap_uint32(meta->s, symtab->nsyms) - 1) * nlist_size)
	{
		ft_error(2, (char*[]){"symtab corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_macho *meta, struct symtab_command *symtab,
							size_t offset)
{
	size_t	nlist_size;

	nlist_size = meta->is64 ? sizeof(struct nlist_64) : sizeof(struct nlist);
	if (offset - swap_uint32(meta->s, symtab->symoff) !=
		swap_uint32(meta->s, symtab->nsyms) * nlist_size)
	{
		ft_error(2, (char*[]){"symtab size corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

/*
** Symtable parsing, done in 2 pass
** First checking for corruption then storing them in table of t_symbol
*/
int	parse_symtable(t_macho *meta, struct symtab_command *symtab)
{
	size_t	i;
	size_t	offset;
	void	*sym;

	i = 0;
	offset = swap_uint32(meta->s, symtab->symoff);
	while (i < swap_uint32(meta->s, symtab->nsyms))
	{
		sym = meta->file->start + offset;
		if (incongruent_ptr(meta, symtab, sym))
			return (0);
		offset += meta->is64 ?
			sizeof(struct nlist_64) : sizeof(struct nlist);
		i++;
	}
	if (incongruent_size(meta, symtab, offset) ||
		!populate_symlist(meta, symtab))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:35:03 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 05:10:58 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_struct(t_macho *meta, struct symtab_command *symtab)
{
	if (swap_uint32(meta->s, symtab->cmdsize) != sizeof(struct symtab_command) ||
		meta->file->end < meta->file->start + swap_uint32(meta->s,
			symtab->symoff) + swap_uint32(meta->s, symtab->strsize))
	{
		ft_error(2, (char*[]){"symtab command corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

/*
** Symbols extration, stored in the metadata struct
*/
int	extract_symbols(t_macho *meta)
{
	size_t		i;
	uint32_t	lc_cmd;

	i = 0;
	while (i < meta->hdr.hdr32.ncmds)
	{
		lc_cmd = swap_uint32(meta->s, ((struct load_command *)meta->lc_tab[i])->cmd);
		if (lc_cmd == LC_SYMTAB)
		{
			if (incongruent_struct(meta, meta->lc_tab[i]) ||
				!parse_symtable(meta, meta->lc_tab[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

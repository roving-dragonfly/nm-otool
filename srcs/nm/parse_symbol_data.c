/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:13:48 by aalves            #+#    #+#             */
/*   Updated: 2019/02/06 19:59:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_symbol(t_macho *meta, t_symbol *sym)
{
    	uint32_t	strx;

		strx = sym->is64 ? sym->nlist.n64.n_un.n_strx :
			sym->nlist.n32.n_un.n_strx;
		if (meta->file->end < meta->file->start +
			swap_uint32(meta->s, sym->symtab->stroff) + strx ||
			strx > swap_uint32(meta->s, sym->symtab->strsize))
	{
		ft_error(2, (char*[]){"string table corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	save_symbol_string(t_macho *meta, t_symbol *sym)
{
	uint32_t	strx;
	size_t		i;

	strx = (sym->is64 ? sym->nlist.n64.n_un.n_strx :
			sym->nlist.n32.n_un.n_strx);
	sym->name = (char*)meta->file->start +
		swap_uint32(meta->s, sym->symtab->stroff) + strx;
	if (!sym->name)
		return (1);
	printf("Saved %s\n", sym->name);
	i = 0;
	while (sym->name[i])
	{
		if (meta->file->end < (void*)(sym->name + i))
		{
			ft_error(2, (char*[]){"symbol name table corrupt : ",
						meta->file->filename}, T_CORRUPT_FILE);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_symbols_data(t_macho *meta)
{
	t_list		*link;

	link = meta->file->sym_list;
	while (link)
	{
		printf("link %p\n", link);
		if (incongruent_symbol(meta, link->content) ||
			!save_symbol_string(meta, link->content))
			return (0);
		link = link->next;
	}
	return (1);
}

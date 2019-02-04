/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_symtable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:14:29 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 18:44:40 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_list	*link_symdata(t_macho *meta, void *sym)
{
    t_symbol		nlist;
	t_list			*link;

	nlist.nlist = *(union u_nlist*)sym;
	if (meta->is64)
	{
		nlist.is64 = 1;
		nlist.nlist.n64.n_un.n_strx = swap_uint32(meta->s, nlist.nlist.n64.n_un.n_strx);
		nlist.nlist.n64.n_desc = swap_uint16(meta->s, nlist.nlist.n64.n_desc);
		nlist.nlist.n64.n_value = swap_uint64(meta->s, nlist.nlist.n64.n_value);
	}
	else
	{
		nlist.is64 = 0;
        nlist.nlist.n32.n_un.n_strx = swap_uint32(meta->s, nlist.nlist.n32.n_un.n_strx);
		nlist.nlist.n32.n_desc = swap_uint16(meta->s, nlist.nlist.n32.n_desc);
		nlist.nlist.n32.n_value = swap_uint32(meta->s, nlist.nlist.n32.n_value);
	}
    if (!(link = ft_lstnew(&nlist, sizeof(t_symbol))))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	return (link);
}

/*
** Symtable allocation, trusts the data
*/
int	populate_symtable(t_macho *meta, struct symtab_command *symtab)
{
	size_t		i;
	size_t		offset;
	size_t		n_syms;
	t_list		*link;

	i = 0;
	offset = swap_uint32(meta->s, symtab->symoff);
	n_syms = swap_uint32(meta->s, symtab->nsyms);
	while (i < n_syms)
	{

		if (!(link = link_symdata(meta, meta->file->start + offset)))
			return (0);
		if (!meta->sym_list)
			meta->sym_list = link;
		else
			ft_lstadd(&meta->sym_list, link);
		offset += meta->is64 ?
			sizeof(struct nlist_64) : sizeof(struct nlist);
		i++;
	}
	return (1);
}

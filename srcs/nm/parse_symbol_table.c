/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:46:49 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 06:50:19 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_static_lib *meta, void *p)
{
	if (meta->file->end < p + sizeof(struct ranlib))
	{
		ft_error(2, (char*[]){"static lib symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_static_lib *meta, uint32_t end_size)
{
    uint32_t		n_sym;

    n_sym = *(uint32_t*)meta->sym_start;
	if (end_size != n_sym)
	{
		ft_error(2, (char*[]){"static lib size corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int	parse_symbol_table(t_static_lib *meta)
{
    struct ranlib	*sym;
    uint32_t		size;
	uint32_t		offset;

	size = *(uint32_t*)meta->sym_start;
	sym = meta->sym_start + sizeof(uint32_t);
	offset = 0;
	while (offset < size)
	{
		if (incongruent_ptr(meta, sym))
			return (0);
		offset += sizeof(struct ranlib);
		sym++;
	}
	meta->str_start = meta->sym_start + size + sizeof(uint32_t);
	if (incongruent_size(meta, offset) ||
		!populate_macho_lst(meta))
		return (0);
	return (1);
}

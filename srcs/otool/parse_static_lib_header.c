/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_static_lib_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:50:27 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:30:15 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	parse_ranlib_table(t_static_lib *meta, void *start)
{
    uint32_t	size;

	size = *(uint32_t*)start;
	if (meta->file->end < start + sizeof(uint32_t) + size * sizeof(struct ranlib) ||
		size % sizeof(struct ranlib))
	{
		ft_error(2, (char*[]){"static library corrupt size : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (0);
	}
	return (1);
}

int	parse_static_lib_header(t_binfile *file, t_static_lib *metadata, void *start)
{
	uint64_t	magic;

	magic = *(uint64_t*)start;
	if (start > file->end - 60)
		return (0);
    metadata->file = file;
    if (magic == T_STATIC_MAGIC || magic == T_STATIC_CIGAM)
        metadata->s = (magic == T_STATIC_MAGIC ? noswap_tab() : swap_tab());
	else
		return (0);
	if (!parse_ranlib_table(metadata, start + 0x58))
		return (0);
	metadata->sym_start = start + 0x58;
	return (1);
}

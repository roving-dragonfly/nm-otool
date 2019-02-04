/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_static_lib_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:50:27 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 20:19:10 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/* static int	set_static_lib_header(t_static_lib *meta, void *start) */
/* { */

/* } */

int	parse_static_lib_header(t_binfile *file, t_static_lib *metadata, void *start)
{
	uint64_t magic;

	magic = *(uint64_t*)start;
	if (start > file->end - 60)
		return (0);
    metadata->file = file;
    if (magic == T_STATIC_MAGIC || magic == T_STATIC_CIGAM)
        metadata->s = (magic == T_STATIC_MAGIC ? noswap_tab() : swap_tab());
	else
		return (0);
	//set_static_lib_header(metadata, start);
	return (1);
}

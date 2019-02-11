/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_static_lib_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:50:27 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 17:20:52 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/* static void	*valid_file_name(t_static_lib *meta, void *start) */
/* { */
/* 	if (!ft_strncmp("#1/", start + sizeof(uint64_t), 3)) */
/* 	{ */
/* 		start += 0x40; */
/* 		if (*(uint32_t*)start != 0x0a602020) */
/* 		{ */
/* 			ft_error(2, (char*[]){"static library corrupt header : ", */
/* 						meta->file->filename}, T_CORRUPT_FILE); */
/* 			return (NULL); */
/* 		} */
/* 		start += sizeof(uint32_t); */
/* 		if (!ft_strcmp(SYMDEF_SORTED, start)) */
/* 		{ */
/* 			start += ft_strlen(SYMDEF_SORTED) + 1; */
/* 			start += (size_t)start % 8; */
/* 			return (start); */
/* 		} */
            
/* 		else if (!ft_strcmp(SYMDEF, start)) */
/* 		{ */
/* 			start += ft_strlen(SYMDEF) + 1; */
/* 			start += (size_t)start % 8; */
/* 			return (start); */
/* 		} */
/* 		else */
/* 		{ */
/* 			ft_error(2, (char*[]){"static library corrupt header : ", */
/* 						meta->file->filename}, T_CORRUPT_FILE); */
/*             return (NULL); */
/* 		} */
/* 	} */
/* 	return (NULL); */
/* } */

static uint32_t	valid_ranlib_header(t_static_lib *meta, void *start)
{
//maybe someday, or never
	return (1);
}

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
	if (!valid_ranlib_header(metadata, start + sizeof(uint64_t)) ||
		!parse_ranlib_table(metadata, start + 0x58))
		return (0);
	metadata->sym_start = start + 0x58;
	return (1);
}

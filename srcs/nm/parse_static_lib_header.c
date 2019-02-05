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

static int	valid_file_name(t_static_lib *meta, void *start)
{
	char	*name;
	int		name_size;
	
	name = start;
	if (!ft_strncmp("#1/", name, 3))
	{
		name += 3;
		name_size = ft_atoi(name);
		name_size += name_size % 8;
        start = start + 60;
		printf("val -> %x\n", swap_int16(*(uint16_t*)start));
		if (swap_int16(*(uint16_t*)start) != (uint16_t)0x0a60)
		{
            
			ft_error(2, (char*[]){"static library corrupt header : ",
						meta->file->filename}, T_CORRUPT_FILE);
            return (0);
		}
		return (1);
	}
	else if (!ft_strcmp(meta->file->filename, name))
		return (1);
	else
		return (0);
}

/* static int	set_static_lib_header(t_static_lib *meta, void *start) */
/* { */
    
	
/*     if () */
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
	if (!valid_file_name(metadata, start + sizeof(uint64_t)))
		return (0);
	//set_static_lib_header(metadata, start);
	return (1);
}

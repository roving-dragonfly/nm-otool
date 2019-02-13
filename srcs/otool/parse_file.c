/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 01:25:53 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 05:21:33 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int parse_file(t_proc_infos *pi, t_binfile *file, void *start)
{
	union u_metadata	meta;

	ft_bzero(&meta, sizeof(union u_metadata));
	if (parse_fat_header(file, &meta.fat, start))
	{
		if (!parse_fat_arch(&meta.fat))
		{
            cleanup_fat(&meta.fat);
			return (0);
 		}
		if (pi->flags & T_FAT_FLAG)
			print_fat_header(pi, &meta.fat);
		if (!explore_fat_archs(pi, &meta.fat))
		{
            cleanup_fat(&meta.fat);
			return (0);
 		}
		cleanup_fat(&meta.fat);
	}
	else if (parse_macho_header(file, &meta.macho, start))
	{
		if (pi->flags & T_MACHO_FLAG)
			print_macho_header(&meta.macho);
		if (!parse_load_commands(&meta.macho) ||
			!parse_segments(&meta.macho))
		{
			cleanup_macho(&meta.macho);
			return (0);
		}
		if (pi->flags & T_TEXT_FLAG)
			print_text_segment(&meta.macho);
		cleanup_macho(&meta.macho);
	}
	else if (parse_static_lib_header(file, &meta.ar, start))
	{
		if (!parse_symbol_table(&meta.ar) || !explore_static_symbols(pi, &meta.ar))
		{
			cleanup_static(&meta.ar);
            return (0);
		}
		cleanup_static(&meta.ar);
	}
	else
	{
		ft_error(2, (char*[]){"Unrecognized format : ", file->filename},
				T_PARSING_FAILED);
		return (0);
	}
	return (1);
}

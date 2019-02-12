/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_static_symbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:23:59 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 06:21:50 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_static_lib *meta, t_static_o *obj)
{
	if (meta->file->end < obj->start + sizeof(struct mach_header))
	{
		ft_error(2, (char*[]){"static library symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int		extract_static_symbols(t_static_lib *meta)
{
	t_binfile		file;
	t_list			*link;

	link = meta->macho_lst;
	while (link->next)
		link = link->next;
	while (link)
	{
		ft_bzero(&file, sizeof(t_binfile));
		if (incongruent_ptr(meta, link->content))
			return (0);
		file.start = ((t_static_o*)link->content)->start;
		file.end = meta->file->end; //maybe get size of file ?
        file.filename = meta->file->filename;
		file.sym_list = meta->file->sym_list;
		file.obj = ((t_static_o*)link->content)->name;
		if (!parse_file(&file, file.start))
			return (0);
		meta->file->sym_list = file.sym_list;
        link = link->prev;
	}
	return (1);
}

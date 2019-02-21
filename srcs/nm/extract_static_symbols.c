/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_static_symbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:23:59 by aalves            #+#    #+#             */
/*   Updated: 2019/02/20 19:37:57 by aalves           ###   ########.fr       */
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

static int	adjusted_offset(t_static_lib *meta, void *hdr)
{
	int	name_size;

	if (ft_strncmp("#1/", hdr, 3))
	{
		ft_error(2, (char*[]){"static lib header corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (0);
	}
	name_size = ft_atoi(hdr + 3);
	return (60 + name_size);
}


static int	explore_by_crappy_jumps(t_static_lib *meta)
{
    void		*ar_hdr;
	uint32_t	size;
	void		*macho_hdr;
	t_binfile	file;

    ar_hdr = meta->str_start + 4;
	macho_hdr = ar_hdr + adjusted_offset(meta, ar_hdr);
	while (macho_hdr < meta->file->end)
	{
		ft_bzero(&file, sizeof(t_binfile));
		size = ft_atoi(ar_hdr + 48);
		file.start = macho_hdr;
		file.end = macho_hdr + size;
        file.filename = meta->file->filename;
		file.sym_list = meta->file->sym_list;
		file.obj = ar_hdr + 60;
		if (!parse_file(&file, file.start))
			return (0);
		ar_hdr += size + 60;
		meta->file->sym_list = file.sym_list;
		if (ar_hdr + 60 > meta->file->end)
			break;
		macho_hdr = ar_hdr + adjusted_offset(meta, ar_hdr);
	}
	return (1);
}

int		extract_static_symbols(t_static_lib *meta)
{
	t_binfile		file;
	t_list			*link;

	link = meta->macho_lst;
	if (!link)
		return (explore_by_crappy_jumps(meta));
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

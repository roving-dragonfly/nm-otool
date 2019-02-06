/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:33:48 by aalves            #+#    #+#             */
/*   Updated: 2019/02/06 17:04:54 by aalves2019/02/06 16:47:45 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_list	*parse_segment32(t_macho *meta, struct segment_command *seg)
{
	t_list		*link;

	if (meta->file->end < (void*)seg + sizeof(struct segment_command))
	{
		ft_error(2, (char*[]){"segment_command corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (NULL);
	}
	if (!(link = ft_lstnew(&((t_segment){(union u_segment*)seg, 0, NULL}), sizeof(t_segment))))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	return (link);
}

static t_list	*parse_segment64(t_macho *meta, struct segment_command_64 *seg)
{
	t_list		*link;

	if (meta->file->end < (void*)seg + sizeof(struct segment_command_64))
	{
		ft_error(2, (char*[]){"segment_command corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (NULL);
	}
	if (!(link = ft_lstnew(&((t_segment){(union u_segment*)seg, 1, NULL}), sizeof(t_segment))))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	return (link);
}

/*
** Parses all segments in lc_tab, stores data in seg_list
*/
int parse_segments(t_macho *meta)
{
	size_t				i;
	struct load_command	*lc;
	t_list				*link;

	i = 0;
	while (i < meta->hdr.hdr32.ncmds)
	{
		link = NULL;
		lc = meta->lc_tab[i];
		if (swap_uint32(meta->s, lc->cmd) == LC_SEGMENT &&
			!(link = parse_segment32(meta, (void*)lc)))
			return (0);
		else if (swap_uint32(meta->s, lc->cmd) == LC_SEGMENT_64 &&
			!(link = parse_segment64(meta, (void*)lc)))
			return (0);
        else if (!link && ++i)
			continue;
		if (!parse_sections(meta, link->content))
			return (0);
		if (!meta->seg_list)
            meta->seg_list = link;
		else
	 		ft_lstadd(&meta->seg_list, link);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:05:58 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:42:51 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	corrupt_section_64(t_macho *meta, struct section_64 *sect)
{
	if (meta->file->end < (void*)sect + sizeof(struct section_64))
	{
		printf("sectname %s\n", sect->sectname);
		ft_error(2, (char*[]){"section 64 corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
    return (0);
}

static int	corrupt_section_32(t_macho *meta, struct section *sect)
{
	if (meta->file->end < (void*)sect + sizeof(struct section))
	{
		ft_error(2, (char*[]){"section 32 corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);

	}
	return (0);
}

static int	populate_sectlist(t_macho *meta, t_segment *seg)
{
	size_t	offset;
    size_t	i;
	size_t	nsects;

	offset = seg->is64 ? sizeof(struct segment_command_64) : sizeof (struct segment_command);
	i = 0;
	if (!(nsects = (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects)))
		return (1);
	if (!(seg->sect_tab = (ft_memalloc(sizeof(void*) * (nsects + 1)))))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (0);
	}
	while (i < nsects)
	{
		seg->sect_tab[i] = seg->pos + offset;
		offset += seg->is64 ? sizeof(struct section_64) : sizeof(struct section);
		i++;
	}
	seg->sect_tab[i] = NULL;
	return (1);
}

int	parse_sections(t_macho *meta, t_segment *seg)
{
	size_t	offset;
	size_t	i;

	offset = seg->is64 ? sizeof(struct segment_command_64) : sizeof (struct segment_command);
	i = 0;
	while (i < (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects))
	{
		if (seg->is64 && corrupt_section_64(meta, seg->pos + offset))
			return (0);
		else if (!seg->is64 && corrupt_section_32(meta, seg->pos + offset))
            return (0);
		offset += seg->is64 ? sizeof(struct section_64) : sizeof(struct section);
		i++;
	}
	if (!populate_sectlist(meta, seg))
		return (0);
	return (1);
}

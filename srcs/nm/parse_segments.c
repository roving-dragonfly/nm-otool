/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:26:41 by aalves            #+#    #+#             */
/*   Updated: 2019/02/08 18:58:00 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	swap_segment(t_macho *meta, t_segment *seg)
{
	seg->seg.s32.cmd = swap_uint32(meta->s, seg->seg.s32.cmd);
	seg->seg.s32.cmdsize = swap_uint32(meta->s, seg->seg.s32.cmdsize);
	if (seg->is64)
	{
        seg->seg.s64.vmaddr = swap_uint64(meta->s, seg->seg.s64.vmaddr);
        seg->seg.s64.vmsize = swap_uint64(meta->s, seg->seg.s64.vmsize);
        seg->seg.s64.fileoff = swap_uint64(meta->s, seg->seg.s64.fileoff);
        seg->seg.s64.filesize = swap_uint64(meta->s, seg->seg.s64.filesize);
		seg->seg.s64.maxprot = swap_uint32(meta->s, seg->seg.s64.maxprot);
		seg->seg.s64.initprot = swap_uint32(meta->s, seg->seg.s64.initprot);
        seg->seg.s64.nsects = swap_uint32(meta->s, seg->seg.s64.nsects);
		seg->seg.s64.flags = swap_uint32(meta->s, seg->seg.s64.flags);
	}
	else
	{
        seg->seg.s32.vmaddr = swap_uint32(meta->s, seg->seg.s32.vmaddr);
        seg->seg.s32.vmsize = swap_uint32(meta->s, seg->seg.s32.vmsize);
		seg->seg.s32.fileoff = swap_uint32(meta->s, seg->seg.s32.fileoff);
        seg->seg.s32.filesize = swap_uint32(meta->s, seg->seg.s32.filesize);
		seg->seg.s32.maxprot = swap_uint32(meta->s, seg->seg.s64.maxprot);
		seg->seg.s32.initprot = swap_uint32(meta->s, seg->seg.s64.initprot);
        seg->seg.s32.nsects = swap_uint32(meta->s, seg->seg.s32.nsects);
        seg->seg.s32.flags = swap_uint32(meta->s, seg->seg.s32.flags);
	}
}

static t_list	*parse_segment32(t_macho *meta, struct segment_command *seg)
{
	t_list		*link;

	if (meta->file->end < (void*)seg + sizeof(struct segment_command))
	{
		ft_error(2, (char*[]){"segment_command corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (NULL);
	}
	if (!(link = ft_lstnew(&((t_segment){*(union u_segment*)seg, 0, (void*)seg, NULL}), sizeof(t_segment))))
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
	if (!(link = ft_lstnew(&((t_segment){*(union u_segment*)seg, 1, (void*)seg, NULL}), sizeof(t_segment))))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	return (link);
}

/* static void print_seg(t_segment *seg) */
/* { */
/*   		if (seg->is64) */
/* 		{ */
/* 			printf("\nSegment 64\n"); */
/* 			printf("name : %s\n", seg->seg.s64.segname); */
/* 			printf("vmaddr : %llx\n", seg->seg.s64.vmaddr); */
/*             printf("vmsize : %llx\n",  seg->seg.s64.vmsize); */
/*             printf("fileoff : %llx\n",  seg->seg.s64.fileoff); */
/*             printf("filesize : %llx\n", seg->seg.s64.filesize); */
/* 			printf("maxprot : %x\n", seg->seg.s64.maxprot); */
/* 			printf("initprot : %x\n", seg->seg.s64.initprot); */
/* 			printf("nsects : %x\n", seg->seg.s64.nsects); */
/* 			printf("flags : %x\n", seg->seg.s64.flags); */
/* 		} */
/* 		else */
/* 		{ */
/* 			printf("\nSegment 32\n"); */
/* 			printf("name : %s\n", seg->seg.s32.segname); */
/* 			printf("vmaddr : %x\n", seg->seg.s32.vmaddr); */
/*             printf("vmsize : %x\n",  seg->seg.s32.vmsize); */
/*             printf("fileoff : %x\n",  seg->seg.s32.fileoff); */
/*             printf("filesize : %x\n", seg->seg.s32.filesize); */
/* 			printf("maxprot : %x\n", seg->seg.s32.maxprot); */
/* 			printf("initprot : %x\n", seg->seg.s32.initprot); */
/*             printf("nsects : %x\n", seg->seg.s32.nsects); */
/* 			printf("flags : %x\n", seg->seg.s32.flags); */
/* 		} */
        
/* } */

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
		swap_segment(meta, link->content);
		if (!parse_sections(meta, link->content))
			return (0);
		if (!meta->file->seg_list)
            meta->file->seg_list = link;
		else
	 		ft_lstadd(&meta->file->seg_list, link);
		i++;
	}
	return (1);
}

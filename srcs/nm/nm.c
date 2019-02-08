/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:03:44 by aalves            #+#    #+#             */
/*   Updated: 2019/02/08 18:59:27 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	main(int argc, char **argv)
{
	int				i;
	int				fd;
	t_proc_infos	*cmd;
	t_binfile		file;

	if (!(cmd = parse_cl(argc, argv)))
		return (1);
	i = -1;
	while ((size_t)++i < cmd->n_files)
	{
		ft_bzero(&file, sizeof(file));
        file.filename = cmd->files[i];
		if (cmd->n_files > 1)//put this in nm printer
		{
			ft_putstr(cmd->files[i]);
			ft_putstr(":\n");
		}
		if (!(fd = open_file(cmd->files[i])))
			continue;
		if (!map_file(&file, fd))
			continue;
		ft_nm(cmd, &file);
		if (unmap_file(&file) || close_file(&file, fd))
			break;
	}
	return (0);
}

static void print_sections(t_segment *seg)
{
    size_t	i = 0;

	while (seg->sect_tab[i])
	{
		printf("Sectname : %s\n", ((struct section*)seg->sect_tab[i])->sectname);
		printf("Segname : %s\n", ((struct section*)seg->sect_tab[i])->segname);
		i++;
	}
}
                            
static void print_seglist(t_binfile *file)
{
	t_list *link = file->seg_list;
	t_segment *seg;

	while (link->next)
		link = link->next;
	
	while (link)
	{
		seg = link->content;
		if (seg->is64)
		{
			printf("\nSegment 64\n");
			printf("name : %s\n", seg->seg.s64.segname);
			printf("vmaddr : %llx\n", seg->seg.s64.vmaddr);
            printf("vmsize : %llx\n",  seg->seg.s64.vmsize);
            printf("fileoff : %llx\n",  seg->seg.s64.fileoff);
            printf("filesize : %llx\n", seg->seg.s64.filesize);
			printf("maxprot : %x\n", seg->seg.s64.maxprot);
			printf("initprot : %x\n", seg->seg.s64.initprot);
			printf("nsects : %x\n", seg->seg.s64.nsects);
			printf("flags : %x\n", seg->seg.s64.flags);
		}
		else
		{
			printf("\nSegment 32\n");
			printf("name : %s\n", seg->seg.s32.segname);
			printf("vmaddr : %x\n", seg->seg.s32.vmaddr);
            printf("vmsize : %x\n",  seg->seg.s32.vmsize);
            printf("fileoff : %x\n",  seg->seg.s32.fileoff);
            printf("filesize : %x\n", seg->seg.s32.filesize);
			printf("maxprot : %x\n", seg->seg.s32.maxprot);
			printf("initprot : %x\n", seg->seg.s32.initprot);
            printf("nsects : %x\n", seg->seg.s32.nsects);
			printf("flags : %x\n", seg->seg.s32.flags);
		}
		print_sections(seg);
		link = link->prev;
	}
}

void	ft_nm(t_proc_infos *pi, t_binfile *file)
{
	if (!parse_file(file, file->start))
		return ;
	sort_symlist(file->sym_list);
	print_seglist(file);
	print_symbols(file->sym_list);
	//check list for invalid ptrs with file
	cleanup_binfile(file);
}

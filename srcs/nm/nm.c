/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:17:26 by aalves            #+#    #+#             */
/*   Updated: 2019/02/06 19:15:32 by aalves2019/02/06 15:10:18 by aalves           ###   ########.fr       */
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

static void print_symbol(t_list *sym_link)
{
	t_symbol *sym = (t_symbol*)sym_link->content;
	printf("Symbol:\n");
    if (sym->is64)
	{
        printf("NAME : %s\n", sym->name);
		printf("n_strx : %.8x\n", sym->nlist.n64.n_un.n_strx);
        printf("n_type : %x\n", sym->nlist.n64.n_type);
		printf("n_sect : %x\n", sym->nlist.n64.n_sect);
        printf("n_desc : %.4x\n", sym->nlist.n64.n_desc);
		printf("n_value : %.16llx\n", sym->nlist.n64.n_value);
	}
	else
	{
		printf("NAME : %s\n", sym->name);
		printf("n_strx : %.8x\n", sym->nlist.n32.n_un.n_strx);
		printf("n_type : %x\n", sym->nlist.n32.n_type);
		printf("n_sect : %x\n", sym->nlist.n32.n_sect);
		printf("n_desc : %.4x\n", sym->nlist.n32.n_desc);
		printf("n_value : %.8x\n", sym->nlist.n32.n_value);
	}
}

static void print_sym_tab(t_binfile *file)
{
    t_list *link;

	link = file->sym_list;
	printf("Printing symtable \n");
	while (link)
	{
		print_symbol(link);
		link = link->next;
	}
}

void	ft_nm(t_proc_infos *cmd, t_binfile *file)
{
	if (!parse_file(file, file->start))
		return ;
	print_sym_tab(file);
	//check list for invalid ptrs with file
	cleanup_binfile(file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:03:44 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 16:43:02 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	main(int argc, char **argv)
{
	int				i;
	int				fd;
	int				ret;
	t_proc_infos	*cmd;
	t_binfile		file;

	if (!(cmd = parse_cl(argc, argv)))
		return (1);
	i = -1;
	while ((size_t)++i < cmd->n_files)
	{
		ft_bzero(&file, sizeof(file));
        file.filename = cmd->files[i];
		if (!(fd = open_file(cmd->files[i])))
			continue;
		if (!map_file(&file, fd))
			continue;
		ret = ft_nm(cmd, &file);
		if (unmap_file(&file) || close_file(&file, fd))
			break;
	}
	return (ret);
}


int	ft_nm(t_proc_infos *pi, t_binfile *file)
{
	if (!parse_file(file, file->start))
		return (1);
	//get_arch_tab(file->sym_list);
	//	sort_symlist(file->sym_list);
	if (pi->n_files > 1)
	{
		ft_putstr(file->filename);
		ft_putstr(":\n"); //maybe do something about after printing
	}
	/* print_symbols(pi, file); */
	cleanup_arch_tab(file->sym_list);
	cleanup_binfile(file);
	return (0);
}

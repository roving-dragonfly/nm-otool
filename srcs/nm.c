/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 00:31:33 by aalves            #+#    #+#             */
/*   Updated: 2019/02/01 00:32:09 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	main(int argc, char **argv)
{
	int			i;
	int			fd;
	t_command	*cmd;
	t_binfile	file;

	if (!(cmd = parse_cl(argc, argv)))
		return (1);
	i = -1;
	while ((size_t)++i < cmd->n_files)
	{
        file.filename = cmd->files[i];
		if (cmd->n_files > 1)//put this in nm
		{
			ft_putstr(cmd->files[i]);
			ft_putstr(":\n");
		}
		if (!(fd = open_file(cmd->files[i])))
			continue;
		if (!map_file(&file, fd))
			continue;
//		ft_nm(&file);
		if (unmap_file(&file) || close_file(&file, fd))
			break;
	}
	return (0);
}

/* int ft_nm(int fd) */
/* { */


/* } */

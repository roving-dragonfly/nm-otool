/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:17:26 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 19:18:04 by aalves           ###   ########.fr       */
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

void	ft_nm(t_proc_infos *cmd, t_binfile *file)
{
	if (!parse_file(file, file->start))
		return ;
}

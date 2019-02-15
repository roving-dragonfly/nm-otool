/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:41:04 by aalves            #+#    #+#             */
/*   Updated: 2019/02/15 12:06:34 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int	main(int argc, char **argv)
{
	int				i;
	int				fd;
	int				ret;
	t_proc_infos	*pi;
	t_binfile		file;

	if (!(pi = parse_cl(argc, argv)))
		return (1);
	if (!pi->flags)
		pi->flags |= T_TEXT_FLAG;
	i = -1;
	while ((size_t)++i < pi->n_files)
	{
		ft_bzero(&file, sizeof(file));
        file.filename = pi->files[i];
		if (!(fd = open_file(pi->files[i])))
			continue;
		if (!map_file(&file, fd))
			continue;
		ret = ft_otool(pi, &file);
		if (unmap_file(&file) || close_file(&file, fd))
			break;
	}
	return (ret);
}

int	ft_otool(t_proc_infos *pi, t_binfile *file)
{
	if (!parse_file(pi, file, file->start))
		return (1);
	return (0);
}

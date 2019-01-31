/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:29:23 by aalves            #+#    #+#             */
/*   Updated: 2019/01/31 22:15:16 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	main(int argc, char **argv)
{
	int			i;
	int			fd;
	t_binfile	file;

	i = 0;
	while (++i < argc)
	{
        file.file = argv[i];
		if (!(fd = open_file(argv[i])))
			continue;
		if (!map_file(&file, fd))
			continue;
//		ft_nm(&file);
		unmap_file(&file);
		close_file(&file, fd);
	}
	return (0);
}

/* int ft_nm(int fd) */
/* { */


/* } */

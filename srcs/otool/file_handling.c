/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:46 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:53:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error(2, (char*[]){"open : ", filename}, T_OPEN_FAILED);
		return (0);
	}
    return (fd);
}

int		close_file(t_binfile *file, int fd)
{
	if (close(fd))
	{
		ft_error(2, (char*[]){"close : ", file->filename}, T_CLOSE_FAILED);
		return (1);
	}
	return (0);
}

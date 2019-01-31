/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 21:50:46 by aalves            #+#    #+#             */
/*   Updated: 2019/01/31 22:02:51 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

void	close_file(t_binfile *file, int fd)
{
	if (close(fd))
		ft_error_exit(2, (char*[]){"close : ", file->file}, T_CLOSE_FAILED);
}

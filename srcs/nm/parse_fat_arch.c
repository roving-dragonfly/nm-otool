/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fat_arch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:41:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/02 18:55:59 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_fat *meta, void *p)
{
	if (p < (void*)&meta->hdr || p > meta->file->end)
	{
        ft_error(2, (char*[]){"fat_arch corrupted :",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int	parse_fat_arch(t_fat *meta)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = (void*)&meta->hdr;
	while (i < meta->hdr.nfat_arch)
	{
		if (incongruent_ptr(meta, ptr))
			return (0);
		if (meta->is64)
		{
			printf("offset : %llx\n", swap_uint64(meta->s, ((struct fat_arch_64*)ptr)->offset));
			ptr += sizeof(struct fat_arch_64);
		}
        else
		{
			printf("offset : %x\n", swap_uint32(meta->s, ((struct fat_arch*)ptr)->offset));
			ptr += sizeof(struct fat_arch);
		}
		i++;
	}
	return (1);
}

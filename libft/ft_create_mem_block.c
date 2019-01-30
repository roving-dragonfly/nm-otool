/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_mem_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:56:03 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:29:27 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mem_block	*ft_create_mem_block(uint64_t capacity)
{
	t_mem_block	*mem_block;

	while (!(mem_block = (t_mem_block*)ft_memalloc(capacity
			+ sizeof(t_mem_block))))
	{
		capacity >>= 2;
		if (MEM_BLOCK_LIMIT > capacity)
		{
			ft_error(1, (char*[]){MALLOC_FAILURE}, 0);
			exit(EXIT_FAILURE);
		}
	}
	mem_block->capacity = capacity;
	mem_block->block = (((unsigned char*)mem_block) + sizeof(t_mem_block));
	return (mem_block);
}

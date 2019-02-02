/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_block_push_back_elem.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:51 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:51 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mem_block_push_back_elem(t_mem_block *mem_block
									, void *elem, uint32_t size)
{
	while (mem_block->next)
		mem_block = mem_block->next;
	if (mem_block->offset + size <= mem_block->capacity)
	{
		ft_memcpy((unsigned char*)mem_block->block
				+ mem_block->offset, elem, size);
		mem_block->offset += size;
	}
	else
	{
		mem_block->next = ft_create_mem_block(mem_block->capacity * 2);
		return (ft_mem_block_push_back_elem(mem_block->next, elem, size));
	}
	return ((unsigned char*)mem_block->block + mem_block->offset - size);
}

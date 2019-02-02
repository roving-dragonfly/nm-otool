/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:54 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:54 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	*longword_ptr;
	unsigned long	*ptr;
	unsigned int	i;

	i = 0;
	while (i < n % 8)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	longword_ptr = (unsigned long*)(src + i);
	ptr = (unsigned long*)(dst + i);
	while (i < n)
	{
		*ptr++ = *longword_ptr++;
		i += 8;
	}
	return (dst);
}

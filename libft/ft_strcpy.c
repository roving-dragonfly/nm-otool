/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:08 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:08 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned long	*longword_ptr;
	unsigned long	*longword_dst;
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(src);
	i = 0;
	while (i < len % 8)
	{
		dst[i] = src[i];
		i++;
	}
	longword_ptr = (unsigned long*)(src + i);
	longword_dst = (unsigned long*)(dst + i);
	while (i < len)
	{
		*longword_dst++ = *longword_ptr++;
		i += 8;
	}
	dst[len] = '\0';
	return (dst);
}

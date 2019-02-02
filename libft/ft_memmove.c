/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:55 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int		i;

	if (dest > src)
	{
		i = len - 1;
		while (i >= 0)
		{
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}

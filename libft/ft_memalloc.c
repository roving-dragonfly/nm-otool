/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:52 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:52 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (unsigned char*)malloc(size)))
		return (0);
	ft_bzero(mem, size);
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:13 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:13 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		size_dst;
	char	*tmp_src;
	size_t	i;
	int		u;

	u = 0;
	size_dst = ft_strlen(dst);
	i = 0;
	tmp_src = (char *)src;
	while (i < size && dst[i])
		i++;
	if (i == size)
		return (ft_strlen(tmp_src) + i);
	while (i < size - 1)
		dst[i++] = src[u++];
	dst[i] = '\0';
	return (ft_strlen(tmp_src) + size_dst);
}

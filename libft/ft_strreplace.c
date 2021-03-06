/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:19 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:19 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strreplace(char const *str, uint32_t start
						, uint32_t end, char const *src)
{
	uint32_t	len;
	uint32_t	str_len;
	uint32_t	src_len;
	char		*buf;

	buf = NULL;
	if (!str || !src)
		return (NULL);
	src_len = ft_strlen(src);
	str_len = ft_strlen(str);
	len = str_len + src_len;
	if (!(buf = ft_memalloc(len + 1)))
		exit(EXIT_FAILURE);
	if (start < str_len)
		ft_strncpy(buf, str, start);
	ft_strcpy(buf + start, src);
	if (end < str_len)
		ft_strcpy(buf + start + src_len, str + end);
	return (buf);
}

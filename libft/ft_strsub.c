/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:42:48 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:19:40 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	str = ft_strncpy(str, (char*)s + start, len);
	str[len] = '\0';
	return (str);
}

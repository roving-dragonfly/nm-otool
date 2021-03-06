/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:09 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:09 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*tmp;
	unsigned int	len;

	len = ft_strlen(s1);
	if (!(tmp = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	ft_strcpy(tmp, (char*)s1);
	tmp[len] = ((char*)s1)[len];
	return (tmp);
}

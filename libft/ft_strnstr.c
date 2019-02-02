/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:18 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:18 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		u;

	i = 0;
	while (big[i] && i < len)
	{
		u = 0;
		while (big[i + u] == little[u] && big[i + u] && i + u < len)
			u++;
		if (!little[u])
			return ((char*)big + i);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:20 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:20 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int	u;

	i = 0;
	while (big[i])
	{
		u = 0;
		while (big[i + u] == little[u] && big[i + u])
			u++;
		if (!little[u])
			return ((char*)big + i);
		i++;
	}
	if (!ft_strlen((char*)big) && !(ft_strlen((char*)little)))
		return ((char *)big);
	return (NULL);
}

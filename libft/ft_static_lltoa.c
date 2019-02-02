/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_lltoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:03 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:03 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline uint32_t	ft_countnbr(int64_t nbr)
{
	uint32_t		len;

	len = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char					*ft_static_lltoa(int64_t nbr)
{
	static char		str[sizeof("18446744073709551615")];
	uint32_t		len;
	uint32_t		i;
	uint8_t			neg;

	len = ft_countnbr(nbr);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
		neg = 1;
		str[0] = '-';
	}
	else
		neg = 0;
	i = len;
	while (i > neg)
	{
		i--;
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	str[len] = '\0';
	return (str);
}

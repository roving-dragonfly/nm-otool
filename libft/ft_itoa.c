/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:39 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:39 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int			ft_countnbr(int nbr)
{
	int				len;
	long			div;
	unsigned int	nb;

	len = 0;
	div = 1;
	nb = nbr;
	if (nbr < 0)
	{
		nb = -nbr;
		len++;
	}
	if (!nbr)
		return (1);
	while (nb / div)
	{
		len++;
		div *= 10;
	}
	return (len);
}

static int			ft_putnbr_base(int value, char *base, char *str, int i)
{
	unsigned int	nb;
	long int		tmp;

	nb = value;
	if (value < 0)
	{
		nb = -value;
		str[i++] = '-';
	}
	else if (value < 0)
		nb = -value;
	tmp = nb;
	if (tmp > 9)
	{
		i = ft_putnbr_base(nb / 10, base, str, i);
		return (ft_putnbr_base(nb % 10, base, str, i));
	}
	else
	{
		str[i++] = base[nb];
		return (i);
	}
}

char				*ft_itoa(int nbr)
{
	char			*str;
	int				len;

	len = ft_countnbr(nbr);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	ft_putnbr_base(nbr, "0123456789", str, 0);
	str[len] = '\0';
	return (str);
}

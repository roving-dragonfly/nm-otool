/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:56 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:56 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_pow(int nbr, unsigned int exponent)
{
	if (exponent == 0)
		return (1);
	else if (exponent == 1)
		return (nbr);
	else
		return (ft_pow(nbr, exponent - 1) * nbr);
}

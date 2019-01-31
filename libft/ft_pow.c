/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:28:32 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:29:25 by aalves           ###   ########.fr       */
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
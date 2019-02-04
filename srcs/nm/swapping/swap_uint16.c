/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint16.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:48:12 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 16:48:53 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint16_t	swap_uint16(t_swap *s, uint16_t n)
{
	return (s->tab->swap_uint16(n));
}

uint16_t rev_uint16(uint16_t n)
{
	return (swap_int16(n));
}

uint16_t std_uint16(uint16_t n)
{
    return (n);
}

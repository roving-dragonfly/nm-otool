/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:39:55 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:50:41 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint32_t	swap_uint32(t_swap *s, uint32_t n)
{
	return (s->tab->swap_uint32(n));
}

uint32_t rev_uint32(uint32_t n)
{
	return (swap_int32(n));
}

uint32_t std_uint32(uint32_t n)
{
    return (n);
}

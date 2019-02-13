/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:39:55 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:50:52 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint64_t	swap_uint64(t_swap *s, uint64_t n)
{
	return (s->tab->swap_uint64(n));
}

uint64_t rev_uint64(uint64_t n)
{
	return (swap_int64(n));
}

uint64_t std_uint64(uint64_t n)
{
    return (n);
}

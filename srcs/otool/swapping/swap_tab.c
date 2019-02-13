/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:32:44 by aalves            #+#    #+#             */
/*   Updated: 2019/02/13 01:50:26 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

t_swap	*swap_tab(void)
{
	static struct s_swap_interface swap;
	static t_swap tab;

    swap = (struct s_swap_interface)
		{rev_uint16,
		 rev_uint32,
		 rev_uint64};
	tab.tab = &swap;
	return (&tab);
}

t_swap	*noswap_tab(void)
{
	static struct s_swap_interface noswap;
	static t_swap tab;

    noswap = (struct s_swap_interface)
		{std_uint16,
		 std_uint32,
		std_uint64};
	tab.tab = &noswap;
	return (&tab);
}

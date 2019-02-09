/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:20:07 by aalves            #+#    #+#             */
/*   Updated: 2019/02/09 22:20:16 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t		same_arch(t_symbol *sym, struct s_arch *arch)
{
	return (sym->cpu == arch->type &&
			sym->cpu_sub == arch->sub);
}

struct s_arch	get_default_arch(t_list *sym_list)
{
	uint32_t	is64;
	t_list		*link;
    struct s_arch	arch;

    is64 = (sizeof(void*) == 8 ? 1 : 0);

    link = sym_list;
	while (link->next)
		link = link->next;
	while (link)
	{
		if (((t_symbol*)link->content)->is64 == is64)
		{
			arch.type = ((t_symbol*)link->content)->cpu;
			arch.sub = ((t_symbol*)link->content)->cpu_sub;
			return (arch);
		}
		link = link->prev;
	}
	arch.type = ((t_symbol*)link->content)->cpu;
	arch.sub = ((t_symbol*)link->content)->cpu_sub;
	return (arch);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:56:02 by aalves            #+#    #+#             */
/*   Updated: 2019/02/09 19:16:51 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Section counting begins a 1, assumes data is valid
*/
static void	print_section_type(t_symbol *sym, uint8_t type)
{
    char *sect_name;

	sect_name = (sym->is64 ? ((struct section_64*)sym->section)->sectname :
				 ((struct section*)sym->section)->sectname);
	if (!ft_strcmp(sect_name, "__bss"))
        ft_putchar(((type & N_EXT) ? 'B' : 'b'));
	else if (!ft_strcmp(sect_name, "__data"))
		ft_putchar(((type & N_EXT) ? 'D' : 'd'));
    else if (!ft_strcmp(sect_name, "__text"))
		ft_putchar(((type & N_EXT) ? 'T' : 't'));
	else if (!ft_strcmp(sect_name, "__common") ||
			 !ft_strcmp(sect_name, "__const"))
		ft_putchar(((type & N_EXT) ? 'S' : 's'));
}

void print_type(t_symbol *sym)
{
	uint8_t	type;

	type = (sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type);
	if (type & N_STAB)
		ft_putchar('N');
    /* else if ((type & N_TYPE) == N_UNDF && (type & N_EXT)) */
	/* 	ft_putchar('C'); */
	else if ((type & N_TYPE) == N_UNDF)
		ft_putchar('U');
	else if ((type & N_TYPE) == N_ABS)
        ft_putchar('A');
    else if ((type & N_TYPE) == N_SECT)
		print_section_type(sym, type);
	else
		ft_putchar('?');
}

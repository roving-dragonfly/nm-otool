/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:56:02 by aalves            #+#    #+#             */
/*   Updated: 2019/02/07 21:38:59 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void print_type(t_symbol *sym)
{
	uint8_t	type;

	type = (sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type);
    /* printf("~~ %s ~~\n", ft_static_ulltoa_base(type, "01")); */
	/* printf("~~ %s ~~\n", ft_static_ulltoa_base((type & N_TYPE) >>1, "01")); */
	if (type & N_STAB)
		ft_putchar('N');
	else if ((type & N_TYPE) == N_UNDF)
        ft_putchar('U');
	else if ((type & N_TYPE) == N_ABS)
        ft_putchar('A');
    //	else if (type->type == N_SECT) > find what the fuck the printing logic is
	else
		ft_putchar('?');
}

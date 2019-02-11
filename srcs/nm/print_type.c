/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:56:02 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 16:10:53 by aalves           ###   ########.fr       */
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
	if (!ft_strncmp("__bss", sect_name, 5))
        ft_putchar(((type & N_EXT) ? 'B' : 'b'));
	else if (!ft_strncmp("__data", sect_name, 6))
		ft_putchar(((type & N_EXT) ? 'D' : 'd'));
    else if (!ft_strncmp("__text", sect_name, 6))
        ft_putchar(((type & N_EXT) ? 'T' : 't'));
    else
		ft_putchar(((type & N_EXT) ? 'S' : 's'));
	/* else if (!ft_strncmp("__common", sect_name, 8) || */
    /*          !ft_strncmp("__const", sect_name, 7) || */
	/* 		 !ft_strncmp("__class", sect_name, 7) || */
	/* 		 !ft_strncmp("__cstring", sect_name, 9) || */
	/* 		 !ft_strncmp("__gcc_except_tab", sect_name, 16) || */
    /*          !ft_strncmp("__objc_ivar", sect_name, 11) || */
	/* 		 !ft_strncmp("__objc_const", sect_name, 12) || */
    /*          !ft_strncmp("__objc_classname", sect_name, 16) || */
    /*          !ft_strncmp("__objc_methname", sect_name, 15) || */
    /*          !ft_strncmp("__objc_methtype", sect_name, 15) || */
	/* 		 !ft_strncmp("__objc_nlclslist", sect_name, 16) || */
    /*          !ft_strncmp("__objc_data", sect_name, 11) || */
    /*          !ft_strncmp("__program_vars", sect_name, 14) || */
    /*          !ft_strncmp("__xcrun_shim", sect_name, 12) || */
	/* 		 !ft_strncmp("__interpose", sect_name, 11) || */
	/* 		 !ft_strncmp("__crash_info", sect_name, 12)) */
    /*     ft_putchar(((type & N_EXT) ? 'S' : 's')); */
}

void print_type(t_symbol *sym)
{
	uint8_t	type;

	type = (sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type);
	if (type & N_STAB)
		ft_putchar('N');
	else if ((type & N_TYPE) == N_UNDF)
		ft_putchar('U');
	else if ((type & N_TYPE) == N_ABS)
		ft_putchar('A');
    else if ((type & N_TYPE) == N_SECT)
		print_section_type(sym, type);
	else if ((sym->is64 ? sym->nlist.n64.n_desc : sym->nlist.n32.n_desc)
			 == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
		ft_putchar('I');
	else
		ft_putchar('?');
}

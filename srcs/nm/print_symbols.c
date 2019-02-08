/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:39:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/08 19:31:48 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void print_address(t_symbol *sym)
{
	char	*val;
	size_t	i;
	
	if (!(sym->is64 ? sym->nlist.n64.n_value : sym->nlist.n32.n_value))
	{
		if (sym->is64)
			ft_putstr("                ");
		else
			ft_putstr("        ");
	}
	else
	{
		if (sym->is64)
			val = ft_static_ulltoa_base(sym->nlist.n64.n_value,
										"0123456789ABCDEF");
		else
			val = ft_static_ulltoa_base(sym->nlist.n32.n_value,
										"0123456789ABCDEF");
		i = (sym->is64 ? 16 : 8) - ft_strlen(val);
        while (i--)
			ft_putchar('0');
		ft_putstr(val);
	}
}

static void	print_symbol(t_binfile *file, t_symbol *sym)
{
	print_address(sym);
    ft_putchar(' ');
	print_type(file, sym);
	ft_putchar(' ');
	ft_putstr(sym->name);
	ft_putchar('\n');	
}

static void print_sym_tab(t_binfile *file)
{
	t_list		*link;
	t_symbol	*sym;

	link = file->sym_list;
	while (link)
	{
		sym = link->content;
		if (sym->is64)
			print_symbol(file, link->content);
		link = link->next;
	}
}

void print_symbols(t_binfile *file)
{
    uint32_t is64;

	is64 = (sizeof(void*) == 8 ? 1 : 0);

	print_sym_tab(file);
}

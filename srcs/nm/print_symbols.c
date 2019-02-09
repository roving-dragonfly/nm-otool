/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:39:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/09 19:03:29 by aalves           ###   ########.fr       */
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
										"0123456789abcdef");
		else
			val = ft_static_ulltoa_base(sym->nlist.n32.n_value,
										"0123456789abcdef");
		i = (sym->is64 ? 16 : 8) - ft_strlen(val);
        while (i--)
			ft_putchar('0');
		ft_putstr(val);
	}
}

static void	print_symbol(t_symbol *sym)
{
	print_address(sym);
    ft_putchar(' ');
	print_type(sym);
	ft_putchar(' ');
	ft_putstr(sym->name);
	ft_putchar('\n');	
}

static uint32_t	filter_syms(t_proc_infos *pi, t_symbol *sym)
{
	if (sym->is64 != (sizeof(void*) == 8 ? 1 : 0))
		return (0);
	if (((sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type) & N_STAB)
		&& !(pi->flags & T_DEBUG_FLAG))
        return (0);
	return (1);

}

static void print_sym_tab(t_proc_infos *pi, t_list *sym_list)
{
	t_list		*link;
	t_symbol	*sym;

	link = sym_list;
	while (link)
	{
		sym = link->content;
		if (filter_syms(pi, sym))
			print_symbol(link->content);
		link = link->next;
	}
}

void print_symbols(t_proc_infos *pi, t_list *sym_list)
{
	print_sym_tab(pi, sym_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:39:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 08:34:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void print_address(t_symbol *sym)
{
	char	*val;
	size_t	i;

	//!(sym->is64 ? sym->nlist.n64.n_value : sym->nlist.n32.n_value)
	if (((sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type) & N_TYPE) == N_UNDF)
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

static uint32_t	filter_syms(t_proc_infos *pi, t_symbol *sym, struct s_arch *arch, char *obj)
{

	if (sym->arch.type != arch->type || sym->arch.sub != arch->sub)
		return (0);
	if (obj && (sym->obj != obj))
		return (0);
	if (((sym->is64 ? sym->nlist.n64.n_type : sym->nlist.n32.n_type) & N_STAB)
		&& !(pi->flags & T_DEBUG_FLAG))
        return (0);
	return (1);
}

static void print_sym_list(t_proc_infos *pi, t_list *sym_list, struct s_arch *arch, char *obj)
{
	t_list			*link;
	t_symbol		*sym;

	link = sym_list;
	while (link)
	{
		sym = link->content;
		if (filter_syms(pi, sym, arch, obj))
			print_symbol(sym);
		link = link->next;
	}
}

static void	print_obj_name(t_binfile *file, char *name)
{
	ft_putchar('\n');
	ft_putstr(file->filename);
    ft_putchar('(');
	ft_putstr(name);
	ft_putstr("):\n");
}

static int	printed(char **tab, char *obj)
{
    size_t	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], obj))
			return (1);
		i++;
	}
	tab[i] = obj;
	return (0);
}

static void	print_by_obj(t_proc_infos *pi, t_binfile *file, struct s_arch *arch)
{
	t_list			*link;
	t_symbol		*sym;
	char			*objs[1024];

	link = file->sym_list;
	ft_bzero(objs, sizeof(objs));
	while (link)
	{
		sym = link->content;
		link = link->next;
		if (sym->arch.type != arch->type || sym->arch.sub != arch->sub)
			continue;
		if (sym->obj && !printed(objs, sym->obj))
		{
			print_obj_name(file, sym->obj);
            print_sym_list(pi, file->sym_list, arch, sym->obj);
			continue;
		}
		else if (!sym->obj)
		{
			print_sym_list(pi, file->sym_list, arch, NULL);
			break;
		}
	}
}


void print_symbols(t_proc_infos *pi, t_binfile *file)
{
	size_t	i;
    struct s_arch	*arch_tab;
	struct s_arch	*default_arch;

	arch_tab = get_arch_tab(file->sym_list);
	default_arch = get_default_arch(arch_tab, file->sym_list);
	if (!(pi->flags & T_ARCHS_FLAG) && default_arch)
		print_by_obj(pi, file, default_arch);
	else
	{
		i = 0;
		while (arch_tab[i].type)
		{
			if (count_archs(arch_tab) > 1)
			{
				ft_putchar('\n');
				print_arch_infos(file->filename, &arch_tab[i]);
			}
			print_by_obj(pi, file, &arch_tab[i]);
			i++;
		}
	}
}

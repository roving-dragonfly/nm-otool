/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:56:02 by aalves            #+#    #+#             */
/*   Updated: 2019/02/08 20:04:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Section counting begins a 1
*/
static void *get_section(t_binfile *file, uint8_t n)
{
	uint8_t		i;
	t_list		*link;
	t_segment	*seg;

	link = file->seg_list;
	while (link->next)
		link = link->next;
	i = 1;
	while (link)
	{
		seg = link->content;
		if (i + (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects) >= n)
            break;
		i += (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects);
		link = link->prev;
	}
	if (!link && (i + (seg->is64 ? seg->seg.s64.nsects : seg->seg.s32.nsects) < n))
	{
		ft_error(2, (char*[]){"symbol corrupt : ",
					file->filename}, T_CORRUPT_FILE);
		return (NULL);
	}
    return (seg->sect_tab[n - i]);
}

static void	put_section_type(t_binfile *file, t_symbol *sym)
{
	void	*section;

	if (!(section = get_section(file, (sym->is64 ? sym->nlist.n64.n_sect
								 : sym->nlist.n32.n_sect))))
		return ;

}

void print_type(t_binfile *file, t_symbol *sym)
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
    else if ((type & N_TYPE) == N_SECT)
		put_section_type(file, sym);
	else
		ft_putchar('?');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:31:45 by aalves            #+#    #+#             */
/*   Updated: 2019/02/20 19:43:23 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

size_t		count_archs(struct s_arch *tab)
{
	size_t	i;

	i = 0;
    while (tab[i].type)
		i++;
	return (i);
}

static int		arch_in_tab(struct s_arch *tab, struct s_arch arch)
{
	int	i;

	i = 0;
	while (tab[i].type)
	{
		if (tab[i].type == arch.type &&
			tab[i].sub == arch.sub)
			return (-1);
		i++;
	}
	return (i);
}

struct s_arch	*get_arch_tab(t_list *sym_list)
{
	static struct s_arch	arch_tab[32];
	t_list		*link;
	size_t		pos;

	if (arch_tab[0].type)
		return (arch_tab);
	link = sym_list;
	while (link && link->next)
		link = link->next;
	while (link)
	{
		if ((pos = arch_in_tab(arch_tab, ((t_symbol*)link->content)->arch)) != -1)
			arch_tab[pos] = ((t_symbol*)link->content)->arch;
		link = link->prev;
	}
	return (arch_tab);
}

struct s_arch	*get_default_arch(struct s_arch *arch_tab, t_list *sym_list)
{
	size_t			i;

	i = 0;
	arch_tab = get_arch_tab(sym_list);
	while (arch_tab[i].type)
	{
		if (arch_tab[i].type == CPU_TYPE_X86_64)
			return (&arch_tab[i]);
		i++;
	}
	return (NULL);
}

void		cleanup_arch_tab(t_list *sym_list)
{
	struct s_arch	*tab;

	tab = get_arch_tab(sym_list);
	ft_bzero(tab, sizeof(struct s_arch) * 32);
}

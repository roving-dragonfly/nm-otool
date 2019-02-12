/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_macho_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:26:25 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 06:45:34 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_static_lib *meta, void *p)
{
	if (meta->file->end < p + 60)
	{
		ft_error(2, (char*[]){"static lib macho corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

/*
** Static headers varies in size
*/
static int	adjusted_offset(t_static_lib *meta, void *hdr)
{
	int	name_size;

	if (ft_strncmp("#1/", hdr, 3))
	{
		ft_error(2, (char*[]){"static lib header corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (0);
	}
	name_size = ft_atoi(hdr + 3);
	return (60 + name_size);
}

static int	already_in_macholst(t_static_lib *meta, struct ranlib *sym, int hdr_size)
{
    t_list	*link;

	link = meta->macho_lst;
	while (link)
	{
		if (meta->file->start + sym->ran_off + hdr_size == link->content)
			return (1);
		link = link->next;
	}
	return (0);
}

static t_list	*get_o_link(t_static_lib *meta, struct ranlib *sym, int hdr_size)
{
	t_list		*link;
	t_static_o	obj;

	obj.start = meta->file->start + sym->ran_off + hdr_size;
	obj.name = meta->file->start + sym->ran_off + 60;
	if (!(link = ft_lstnew(&obj, sizeof(t_static_o))))
	{
		ft_error(2, (char*[]){"malloc error : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	return (link);
}

int	populate_macho_lst(t_static_lib *meta)
{
    struct ranlib	*sym;
	uint32_t		size;
	t_list			*link;
	int				hdr_size;

	size = *(uint32_t*)meta->sym_start;
	sym = meta->sym_start + sizeof(uint32_t);
	while ((void*)sym < meta->sym_start + size)
	{
		if (incongruent_ptr(meta, meta->file->start + sym->ran_off) ||
			!(hdr_size = adjusted_offset(meta, meta->file->start + sym->ran_off)))
			return (0);
		if (!already_in_macholst(meta, sym, hdr_size))
        {
			if (!(link = get_o_link(meta, sym, hdr_size)))
				return (0);
			if (!meta->macho_lst)
				meta->macho_lst = link;
			else

				ft_lstadd(&meta->macho_lst, link);
		}
		sym++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_static_symbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:23:59 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 18:05:06 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_static_lib *meta, void * p)
{
	if (meta->file->end < p + 0x50)
	{
		ft_error(2, (char*[]){"static library symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int		extract_static_symbols(t_static_lib *meta)
{
    struct ranlib	*sym;
	size_t			i;
	t_binfile		obj;

	i = 0;
	while (meta->sym_tab[i])
	{
		sym = meta->sym_tab[i];
		ft_bzero(&obj, sizeof(t_binfile));
		if (incongruent_ptr(meta, meta->file->start + sym->ran_off))
			return (0);
		obj.start = meta->file->start + sym->ran_off + 0x50;
		obj.end = meta->file->end;
        obj.filename = meta->file->filename;
		obj.sym_list = meta->file->sym_list;
		if (!parse_file(&obj, obj.start))
			return (0);
		meta->file->sym_list = obj.sym_list;
		i++;
	}
	return (1);
}

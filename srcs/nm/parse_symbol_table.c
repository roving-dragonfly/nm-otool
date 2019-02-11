/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:46:49 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 17:53:17 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	incongruent_ptr(t_static_lib *meta, void *p)
{
	if (meta->file->end < p + sizeof(struct ranlib))
	{
		printf("p > %p\n", p);
		ft_error(2, (char*[]){"static lib symbol corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_static_lib *meta, uint32_t end_size)
{
    uint32_t		n_sym;

    n_sym = *(uint32_t*)meta->sym_start;
	if (end_size != n_sym)
	{
		ft_error(2, (char*[]){"static lib size corrupt : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static void	**populate_symtab(t_static_lib *meta)
{
    struct ranlib	*sym;
    uint32_t		size;
	uint32_t		i;
	void			**sym_tab;

	size = *(uint32_t*)meta->sym_start;
	sym = meta->sym_start + sizeof(uint32_t);
	i = 0;
	if (!(sym_tab = ft_memalloc(size / sizeof(struct ranlib) + 1)))
	{
		ft_error(2, (char*[]){"malloc failed : ",
					meta->file->filename}, 0);
		return (NULL);
	}
	while (i < size / sizeof(struct ranlib))
	{
		sym_tab[i] = sym;
		i++;
		sym++;
	}
	sym_tab[i] = NULL;
	return (sym_tab);
}

int	parse_symbol_table(t_static_lib *meta)
{
    struct ranlib	*sym;
    uint32_t		size;
	uint32_t		offset;

	size =*(uint32_t*)meta->sym_start;
	sym = meta->sym_start + sizeof(uint32_t);
	offset = 0;
	while (offset < size)
	{
		if (incongruent_ptr(meta, sym))
			return (0);
		offset += sizeof(struct ranlib);
		sym++;
	}
	if (incongruent_size(meta, offset))
		return (0);
	meta->sym_tab = populate_symtab(meta);
	meta->str_start = meta->sym_start + offset + sizeof(uint32_t);
    /* for (int j = 0; meta->sym_tab[j]; j++){ */
	/* 	printf("strx : %u, stroff : %u\n", ((struct ranlib*)meta->sym_tab[j])->ran_un.ran_strx, */
	/* 		   ((struct ranlib*)meta->sym_tab[j])->ran_off); */
	/* } */
	return (1);
}

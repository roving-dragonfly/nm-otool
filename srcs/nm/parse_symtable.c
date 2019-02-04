/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:33:11 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 17:02:25 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void print_symbol(t_macho *meta, void *sym)
{
	printf("Symbol:\n");
    if (meta->is64)
	{
        struct nlist_64 *n64 = (struct nlist_64 *)sym;
        printf("n_strx : %.8x\n", swap_uint32(meta->s, n64->n_un.n_strx));
        printf("n_type : %x\n", n64->n_type);
		printf("n_sect : %x\n", n64->n_sect);
        printf("n_desc : %.4x\n", swap_uint16(meta->s, n64->n_desc));
		printf("n_value : %.16llx\n", swap_uint64(meta->s, n64->n_value));
	}
	else
	{
		struct nlist *n32 = (struct nlist *)sym;
        printf("n_strx : %.8x\n", swap_uint32(meta->s, n32->n_un.n_strx));
		printf("n_type : %x\n", n32->n_type);
		printf("n_sect : %x\n", n32->n_sect);
		printf("n_desc : %.4x\n", swap_uint16(meta->s, n32->n_desc));
		printf("n_value : %.16llx\n", swap_uint64(meta->s, n32->n_value));
	}
}


static int	incongruent_ptr(t_macho *meta, struct symtab_command *symtab,
							void *p)
{
	size_t	nlist_size;

	nlist_size = meta->is64 ? sizeof(struct nlist_64) : sizeof(struct nlist);
	if (p > meta->file->end ||
		p > meta->file->start + swap_uint32(meta->s, symtab->symoff)
		+ (swap_uint32(meta->s, symtab->nsyms) - 1) * nlist_size)
	{
		ft_error(2, (char*[]){"symtab corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

static int	incongruent_size(t_macho *meta, struct symtab_command *symtab,
							size_t offset)
{
	size_t	nlist_size;

	nlist_size = meta->is64 ? sizeof(struct nlist_64) : sizeof(struct nlist);
	if (offset - swap_uint32(meta->s, symtab->symoff) !=
		swap_uint32(meta->s, symtab->nsyms) * nlist_size)
	{
		ft_error(2, (char*[]){"symtab size corrupted : ",
					meta->file->filename}, T_CORRUPT_FILE);
		return (1);
	}
	return (0);
}

int	parse_symtable(t_macho *meta, struct symtab_command *symtab)
{
	size_t	i;
	size_t	offset;
	void	*sym;

	i = 0;
	offset = swap_uint32(meta->s, symtab->symoff);
	while (i < swap_uint32(meta->s, symtab->nsyms))
	{
		sym = meta->file->start + offset;
		if (incongruent_ptr(meta, symtab, sym))
			return (0);
		print_symbol(meta, sym);
		offset += meta->is64 ?
			sizeof(struct nlist_64) : sizeof(struct nlist);
		i++;
	}
	if (incongruent_size(meta, symtab, offset))
		return (0);
	return (1);
}

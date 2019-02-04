/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:30:45 by aalves            #+#    #+#             */
/*   Updated: 2019/02/04 18:59:06 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	free_symlist(t_list *head)
{
	t_list	*next;

	if (head)
	{
		free(head->content);
		next = head->next;
		if (next)
			free_symlist(next);
	}
}

void	cleanup_macho(t_macho *meta)
{
	if (meta->lc_tab)
		free(meta->lc_tab);
    if (meta->sym_list)
        free_symlist(meta->sym_list);

}

void	cleanup_fat(t_fat *meta)
{
	if (meta->arch)
		free(meta->arch);
}

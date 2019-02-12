/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:30:45 by aalves            #+#    #+#             */
/*   Updated: 2019/02/12 06:49:47 by aalves           ###   ########.fr       */
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
		free(head);
		if (next)
			free_symlist(next);
	}
}

static void	free_seglist(t_list *head)
{
	t_list	*next;

	if (head)
	{
		free(((t_segment*)head->content)->sect_tab);
		free(head->content);
		free(head);
		next = head->next;
		free_seglist(next);
	}
}

static void free_macholist(t_list *head)
{
	t_list	*next;

	if (head)
	{
		free(head->content);
		free(head);
		next = head->next;
		free_macholist(next);
	}
}

void	cleanup_binfile(t_binfile *file)
{
	if (file->sym_list)
		free_symlist(file->sym_list);
}

void	cleanup_macho(t_macho *meta)
{
	if (meta->lc_tab)
		free(meta->lc_tab);
	if (meta->seg_list)
		free_seglist(meta->seg_list);
}

void	cleanup_fat(t_fat *meta)
{
	if (meta->arch)
		free(meta->arch);
}

void	cleanup_static(t_static_lib *meta)
{
    if (meta->macho_lst)
		free_macholist(meta->macho_lst);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:30:45 by aalves            #+#    #+#             */
/*   Updated: 2019/02/11 18:10:02 by aalves           ###   ########.fr       */
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

static void	free_seglist(t_list *head)
{
	t_list	*next;
	printf("ayy\n");
	if (head)
	{
		free(((t_segment*)head->content)->sect_tab);
		free(head->content);
		next = head->next;
		if (next)
			free_seglist(next);
	}
}

void	cleanup_binfile(t_binfile *file)
{
	if (file->sym_list)
		free_symlist(file->sym_list);
}

void	cleanup_macho(t_macho *meta)
{
	printf("here\n");
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
	if (meta->sym_tab)
		free(meta->sym_tab);
}

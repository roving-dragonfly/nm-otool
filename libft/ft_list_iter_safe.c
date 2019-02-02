/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter_safe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:43 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:43 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_iter_safe(t_list_head *head, void (*f) (t_list_head *))
{
	t_list_head *entry;
	t_list_head *next;

	entry = head->next;
	while (entry != head)
	{
		next = entry->next;
		f(entry);
		entry = next;
	}
}

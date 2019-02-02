/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:43 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:43 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_iter(t_list_head *head, void (*f) (t_list_head *))
{
	t_list_head *entry;

	entry = head->next;
	while (entry != head)
	{
		f(entry);
		entry = entry->next;
	}
}

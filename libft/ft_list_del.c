/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:42 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_del(t_list_head *link)
{
	link->prev->next = link->next;
	link->next->prev = link->prev;
	link->prev = (void *)0;
	link->next = (void *)0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_between.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:40 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:40 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_add_between(t_list_head *new, t_list_head *prev,
							t_list_head *next)
{
	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;
}

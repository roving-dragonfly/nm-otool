/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:44 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:44 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_move(t_list_head *to_move, t_list_head *head)
{
	ft_list_del(to_move);
	ft_list_add(to_move, head);
}

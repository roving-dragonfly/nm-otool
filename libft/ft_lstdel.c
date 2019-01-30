/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:00:57 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:29:26 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_recursive_del(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst)->next)
		ft_lstdel(&(*alst)->next, del);
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	ft_recursive_del(alst, del);
	*alst = 0;
}

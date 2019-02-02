/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:47 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:47 by aalves           ###   ########.fr       */
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

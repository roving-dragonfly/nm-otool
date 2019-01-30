/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 16:44:35 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:29:26 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_lsttotab(t_list *lst, unsigned int len)
{
	unsigned char	*tab;
	unsigned int	i;
	unsigned int	u;

	i = 0;
	u = 0;
	if (!(tab = (unsigned char*)malloc(lst->content_size * len)))
		return (0);
	while (i < len)
	{
		while (u < lst->content_size)
		{
			tab[i * 4 + u] = ((unsigned char*)lst->content)[u];
			u++;
		}
		u = 0;
		lst = lst->next;
		i++;
	}
	return (tab);
}

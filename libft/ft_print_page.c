/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_page.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:56 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:48:56 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_page(void *addr)
{
	unsigned char	*tmp;
	int				i;

	i = 0;
	tmp = addr - ((unsigned long)4095 & (unsigned long)addr);
	while (i < 4096)
	{
		if (ft_isprint(tmp[i]))
			ft_putchar(tmp[i]);
		else
			ft_putchar('.');
		i++;
		if (!(i % 64))
			ft_putchar('\n');
	}
	ft_putchar('\n');
}

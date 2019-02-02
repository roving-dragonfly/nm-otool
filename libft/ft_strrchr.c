/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:19 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:19 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		if ((char)c == s[i])
			tmp = (char*)s + i;
		i++;
	}
	if ((char)c == s[i])
		tmp = (char*)s + i;
	return (tmp);
}

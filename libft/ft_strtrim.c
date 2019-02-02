/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:21 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:21 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (!s[i])
	{
		if (!(str = ft_strnew(1)))
			return (0);
		return (str);
	}
	start = i;
	i = ft_strlen((char*)s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	end = i - start + 1;
	if (!(str = ft_strsub(s, start, end)))
		return (0);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:15 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:15 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = ft_strlen(s2);
	n = n > i ? i : n;
	i = ft_strlen(s1);
	ft_strncpy(s1 + i, s2, n);
	s1[i + n] = '\0';
	return (s1);
}

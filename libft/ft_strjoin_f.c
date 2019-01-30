/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:15:45 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:19:41 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_f(char *a, char *b, int32_t mode)
{
	char	*str;
	size_t	len;
	size_t	s1_len;

	if (!a || !b)
		return (0);
	s1_len = ft_strlen(a);
	len = s1_len + ft_strlen(b);
	if (!(str = ft_strnew(len)))
		return (0);
	ft_strcpy(str, a);
	ft_strcpy(str + s1_len, b);
	if (mode == 0)
		free(a);
	else if (mode == 1)
		free(b);
	else
	{
		free(a);
		free(b);
	}
	return (str);
}

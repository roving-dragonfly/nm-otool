/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:17 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:17 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t len)
{
	char	*tmp;

	if (!(tmp = ft_strnew(len)))
		exit(EXIT_FAILURE);
	ft_memcpy(tmp, str, len);
	return (tmp);
}

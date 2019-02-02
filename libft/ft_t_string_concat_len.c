/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_concat_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:22 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:22 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_t_string_concat_len(t_string *string
									, char *str, uint32_t str_len)
{
	uint64_t	total_len;

	if (!str || !string)
		return (NULL);
	total_len = string->len + str_len;
	if (total_len >= string->capacity)
	{
		ft_t_string_expand(string);
		return (ft_t_string_concat_len(string, str, str_len));
	}
	else
	{
		ft_memcpy(string->string + string->len, str, str_len);
		string->len = total_len;
		string->string[string->len] = '\0';
	}
	return (string);
}

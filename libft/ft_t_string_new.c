/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:24 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:24 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_t_string_new(uint32_t capacity)
{
	t_string	*string;

	if (!(string = (t_string*)malloc(sizeof(t_string))))
		exit(EXIT_FAILURE);
	string->capacity = capacity;
	if (!(string->string = (char*)malloc(sizeof(char) * (capacity + 1))))
		exit(EXIT_FAILURE);
	ft_memset(string->string, 0, capacity);
	string->len = 0;
	return (string);
}

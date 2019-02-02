/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:49:23 by aalves            #+#    #+#             */
/*   Updated: 2019/01/29 21:49:23 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_t_string_expand(t_string *string)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strnew(string->capacity * 2)))
		exit(EXIT_FAILURE);
	string->capacity *= 2;
	ft_memcpy(tmp, string->string, string->len);
	string->string[string->len] = '\0';
	free(string->string);
	string->string = tmp;
}

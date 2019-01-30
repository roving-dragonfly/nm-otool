/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:19:48 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:19:40 by aalves           ###   ########.fr       */
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

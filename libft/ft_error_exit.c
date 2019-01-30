/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 17:54:27 by aalves            #+#    #+#             */
/*   Updated: 2019/01/23 09:29:27 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_exit(uint32_t n, char **str, int32_t exit_status)
{
	uint32_t	i;

	i = 0;
	ft_putstr_fd(ERROR_NAME_HEADER, 2);
	while (i < n)
	{
		ft_putstr_fd(str[i], 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

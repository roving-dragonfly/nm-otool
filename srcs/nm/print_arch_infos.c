/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arch_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:24:07 by aalves            #+#    #+#             */
/*   Updated: 2019/02/10 21:36:23 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_arch(struct s_arch *arch)
{
    if (arch->type == CPU_TYPE_VAX)
		ft_putstr("vax");
    else if (arch->type == CPU_TYPE_MC680x0)
		ft_putstr("mc680x0");
	else if (arch->type == CPU_TYPE_X86)
		ft_putstr("i386");
	else if (arch->type == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (arch->type == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else if (arch->type == CPU_TYPE_HPPA)
		ft_putstr("hppa");
	else if (arch->type == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (arch->type == CPU_TYPE_ARM64)
		ft_putstr("arm64");
	else if (arch->type == CPU_TYPE_MC88000)
		ft_putstr("mc88000");
	else if (arch->type == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (arch->type == CPU_TYPE_I860)
		ft_putstr("i860");
	else if (arch->type == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (arch->type == CPU_TYPE_POWERPC64)
		ft_putstr("ppc64");
}

void		print_arch_infos(char *filename, struct s_arch *arch)
{

	ft_putstr(filename);
	ft_putstr(" (for architecture ");
	print_arch(arch);
	ft_putstr("):\n");
}

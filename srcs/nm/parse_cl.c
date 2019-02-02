/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:06:39 by aalves            #+#    #+#             */
/*   Updated: 2019/02/01 00:33:22 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	put_usage()
{
	ft_putstr("Usage: ft_nm [option(s)] [file(s)]\n");
	ft_putstr("List symbols in [file(s)] (a.out by default).\n");
	ft_putstr("The options are:\n");
	ft_putstr("-g\t\tDisplay only external symbols\n");
	ft_putstr("-p\t\tDo not sort the symbols\n");
	ft_putstr("-r\t\tReverse sort\n");
}

t_command	*parse_cl(int argc, char **argv)
{
	static t_command	cmd;
	static char			*default_file[1];
	char				flag;

	while ((flag = ft_getopt(argc, argv, T_NM_FLAGS)) != -1)
	{
		if (flag == GETOPT_ERR_CHAR)
		{
			put_usage();
            return (0);
		}
		cmd.flags ^= 1U << (uint64_t)(ft_strchr(T_NM_FLAGS, flag) - T_NM_FLAGS);
	}
	cmd.n_files = argc - g_optind;
	if (!cmd.n_files)
	{
		cmd.files = default_file;
		default_file[0] = "a.out";
		cmd.n_files = 1;
	}
	else
		cmd.files = &argv[g_optind];
	return (&cmd);
}

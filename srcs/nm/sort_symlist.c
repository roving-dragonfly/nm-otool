/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:37:09 by aalves            #+#    #+#             */
/*   Updated: 2019/02/09 20:48:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int32_t	name_sort(t_symbol *a, t_symbol *b)
{
    int	ret;

	ret = ft_strcmp(a->name, b->name);
	if (!ret)
		ret = (a->is64 ? a->nlist.n64.n_value : a->nlist.n32.n_value) -
			(b->is64 ? b->nlist.n64.n_value : b->nlist.n32.n_value);
	return (ret);
}

static uint32_t		list_sorted(t_list *list, int32_t (*f)(t_symbol*, t_symbol*))
{
	if (!list || !list->next)
		return (1);
	if (f(list->content, list->next->content) > 0)
		return (0);
	else
		return (list_sorted(list->next, f));
}
static void			sort_symlist_rec(t_list *list, int32_t (*f)(t_symbol*, t_symbol*))
{
	void	*tmp;

	if (!list || !list->next)
		return ;
	if (f(list->content, list->next->content) > 0)
	{
        tmp = list->content;
		list->content = list->next->content;
		list->next->content = tmp;
        sort_symlist_rec(list, f);
	}
	else
		sort_symlist_rec(list->next, f);
}

void		sort_symlist(t_list *list)
{
	while (!list_sorted(list, name_sort))
		sort_symlist_rec(list, name_sort);
}

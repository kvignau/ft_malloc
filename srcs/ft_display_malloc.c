/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:40:25 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 17:40:27 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t	ft_display(t_block *block, char *type)
{
	t_block		*tmp;
	size_t		total;

	total = 0;
	tmp = block;
	if (!tmp)
		return (0);
	ft_printf("%s: %p\n", type, tmp);
	while (tmp)
	{
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->used)
			{
				ft_printf("%p", tmp->malloc->ptr);
				ft_printf("- %p :", tmp->malloc->ptr + tmp->malloc->size);
				ft_printf("%zu\n", tmp->malloc->size);
				total += tmp->malloc->size;
			}
			tmp->malloc = tmp->malloc->next;
		}
		tmp = tmp->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	total = ft_display(g_lst_types.tiny, "TINY");
	total += ft_display(g_lst_types.small, "SMALL");
	total += ft_display(g_lst_types.large, "LARGE");
	ft_printf("Total : %zu octets\n", total);
}

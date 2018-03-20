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

static void		ft_print_mem(uintmax_t n, size_t base)
{
	char				str[ft_nbrlen(n, base)];
	size_t				len;

	len = ft_nbrlen(n, base) - 1;
	if (n == 0)
		str[len] = '0';
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (base > 10 && n % base > 9) ?
			(n % base) + ('a' - 10) : (n % base) + 48;
		n /= base;
		len--;
	}
	ft_putstr(str);
}

static void		ft_print_all(t_malloc *malloc)
{
	ft_putstr("0x");
	ft_print_mem((uintmax_t)malloc->ptr, 16);
	ft_putstr(" - 0x");
	ft_print_mem((uintmax_t)malloc->ptr + malloc->size, 16);
	ft_putstr(" : ");
	ft_print_mem((uintmax_t)malloc->size, 10);
	ft_putstr("\n");
}

static size_t	ft_display(t_block *block, char *type)
{
	t_block		*tmp;
	size_t		total;

	total = 0;
	tmp = block;
	if (!tmp)
		return (0);
	ft_putstr(type);
	ft_print_mem((uintmax_t)tmp, 16);
	ft_putstr("\n");
	while (tmp)
	{
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->used)
			{
				ft_print_all(tmp->malloc);
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
	total = ft_display(g_lst_types.tiny, "TINY : 0x");
	total += ft_display(g_lst_types.small, "SMALL : 0x");
	total += ft_display(g_lst_types.large, "LARGE : 0x");
	ft_putstr("Total : ");
	ft_print_mem((uintmax_t)total, 10);
	ft_putstr(" octets\n");
}

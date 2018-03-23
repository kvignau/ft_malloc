/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:13:20 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 16:13:23 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t			ft_align_memory(size_t size)
{
	int			add;

	add = size % 16;
	if (add)
		return (size = size + (16 - add));
	return (size);
}

void			ft_free_empty(t_block *block, size_t type)
{
	if (block->next)
		block->next->prev = block->prev;
	block->prev->next = block->next;
	munmap(block, type + sizeof(t_malloc) + sizeof(t_block));
}

void			*ft_add_large(size_t size)
{
	t_block		*block;

	block = NULL;
	size = ft_align_memory(size);
	if (!g_lst_types.large)
	{
		g_lst_types.large =
			crt_block(size + sizeof(t_malloc) + sizeof(t_block));
		if (!g_lst_types.large)
			return (NULL);
		g_lst_types.large->malloc->used = 1;
		return (g_lst_types.large->malloc->ptr);
	}
	block = g_lst_types.large;
	while (block->next)
		block = block->next;
	block->next =
		crt_block(size + sizeof(t_malloc) + sizeof(t_block));
	if (!block->next)
		return (NULL);
	block->last = 0;
	block->next->prev = block;
	block->next->malloc->used = 1;
	return (block->next->malloc->ptr);
}

void			*ft_add_small(size_t size)
{
	t_block		*block;
	void		*ptr;

	block = NULL;
	if (!g_lst_types.small)
	{
		g_lst_types.small =
		crt_block((SMALL + sizeof(t_malloc) + sizeof(t_block)) * 100);
		return (!g_lst_types.small) ? NULL
		: ft_find_space(g_lst_types.small, size);
	}
	block = g_lst_types.small;
	while (block)
	{
		block->malloc = block->first;
		if ((ptr = ft_find_space(block, size)))
			return (ptr);
		if (block->last == 1)
			break ;
		block = block->next;
	}
	block->last = 0;
	block->next = crt_block((SMALL + sizeof(t_malloc) + sizeof(t_block)) * 100);
	block->next->prev = block;
	return (ft_find_space(block->next, size));
}

void			*ft_add_tiny(size_t size)
{
	t_block		*block;
	void		*ptr;

	block = NULL;
	if (!g_lst_types.tiny)
	{
		g_lst_types.tiny =
		crt_block((TINY + sizeof(t_malloc) + sizeof(t_block)) * 100);
		return (!g_lst_types.tiny) ? NULL
		: ft_find_space(g_lst_types.tiny, size);
	}
	block = g_lst_types.tiny;
	while (block)
	{
		block->malloc = block->first;
		if ((ptr = ft_find_space(block, size)))
			return (ptr);
		if (block->last == 1)
			break ;
		block = block->next;
	}
	block->last = 0;
	block->next = crt_block((TINY + sizeof(t_malloc) + sizeof(t_block)) * 100);
	block->next->prev = block;
	return (ft_find_space(block->next, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:45:26 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 17:45:29 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block			*crt_block(size_t type)
{
	t_block		*block;

	block = (t_block *)mmap(0, type, PROTS, MAPS, -1, 0);
	if (block == NULL)
		return (NULL);
	block->unused_end_size = 0;
	block->last = 1;
	block->next = NULL;
	block->prev = NULL;
	block->malloc = (t_malloc *)(block + 1);
	block->first = block->malloc;
	block->malloc->used = 0;
	block->malloc->last = 1;
	block->malloc->size = type - (sizeof(t_malloc) + sizeof(t_block));
	block->malloc->ptr = block->malloc + 1;
	block->malloc->next = NULL;
	return (block);
}

static void		ft_create_malloc(t_malloc **malloc, size_t size)
{
	(*malloc)->last = 0;
	(*malloc)->next = (*malloc)->ptr + (*malloc)->size;
	(*malloc)->next->used = 1;
	(*malloc)->next->last = 1;
	(*malloc)->next->size = size;
	(*malloc)->next->ptr = (t_malloc *)(*malloc)->next + 1;
	(*malloc)->next->next = NULL;
}

void			*ft_find_space(t_block *block, size_t size)
{
	size = ft_align_memory(size);
	while (block->malloc)
	{
		if (block->malloc->used == 0 && block->malloc->size >= size)
		{
			if (block->malloc->last == 1)
				(block->unused_end_size =
					(block->unused_end_size + block->malloc->size) - size)
					? block->malloc->size = size : 0;
			block->malloc->used = 1;
			return (block->malloc->ptr);
		}
		if (block->malloc->last == 1)
		{
			if (block->unused_end_size >= size + sizeof(t_malloc))
			{
				block->unused_end_size =
					block->unused_end_size - (size + sizeof(t_malloc));
				ft_create_malloc(&(block)->malloc, size);
				return (block->malloc->next->ptr);
			}
		}
		block->malloc = block->malloc->next;
	}
	return (NULL);
}

void			*malloc(size_t size)
{
	static int	init_lst = 0;
	void		*ptr;

	ptr = NULL;
	if (size <= 0)
		return (NULL);
	if (init_lst == 0)
	{
		g_lst_types.tiny = NULL;
		g_lst_types.small = NULL;
		g_lst_types.large = NULL;
		init_lst++;
	}
	if (size <= (size_t)TINY)
		ptr = ft_add_tiny(size);
	else if (size <= (size_t)SMALL)
		ptr = ft_add_small(size);
	else
		ptr = ft_add_large(size);
	return (ptr);
}

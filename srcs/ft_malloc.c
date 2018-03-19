/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:47:44 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/03 13:19:52 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block			*ft_create_blocks(size_t type)
{
	t_block		*block;

	block = (t_block *)mmap(0, type * 100, PROTS, MAPS, -1, 0);
	if (block == NULL)
	{
		return (NULL);
	}

	block->unused_end_size = (type * 100) - sizeof(t_malloc) - sizeof(t_block);
	block->last = 1;
	block->next = NULL;
	block->prev = NULL;

	block->malloc = (t_malloc *)(block + 1);
	block->first = block->malloc;
	block->malloc->used = 0;
	block->malloc->last = 1;
	block->malloc->size = 0;
	block->malloc->ptr = block->malloc + 1;
	block->malloc->next = NULL;
	printf("UNUSED SPACE BEGIN -> %zu\n", block->unused_end_size);
	printf("POINTEUR DE DEBUT -> %p\n", block);
	printf("SIZE STRUCT BLOCK -> %zu\n", sizeof(t_block));
	printf("SIZE STRUCT MALLOC -> %zu\n", sizeof(t_malloc));
	printf("POINTEUR APRES STRUCTURE -> %p\n", block->malloc);
	printf("FIRST PTR -> %p\n", block->malloc->ptr);

	return (block);
}

void			*ft_add_malloc(size_t size)
{
	t_block		*block;
	void		*ptr;

	block = NULL;
	if (!lst_types.tiny)
	{
		lst_types.tiny = ft_create_blocks(TINY);
		if (!lst_types.tiny)
			return (NULL);
		ptr = ft_find_space(lst_types.tiny, size);
		ft_putstr("AFTER 1\n");
		return (ptr);
	}
	block = lst_types.tiny;
	while (block)
	{
		block->malloc = block->first;
		ft_printf("\n\nBOUCLE\n\n");
		if ((ptr = ft_find_space(block, size)))
			return ptr;
		ft_printf("\n\nLE POINTEUR PTR %p\n\n", ptr);
		if (block->last == 1)
			break;
		block = block->next;
	}
	block->last = 0;
	block->next = ft_create_blocks(TINY);
	return (ft_find_space(block->next, size));
}

// size_t			ft_mem_align(t_malloc )
// {

// }

void			*ft_find_space(t_block *block, size_t size)
{
	while (block->malloc) {
		printf("\n\nDANS WHILE\n\n");
		if (block->malloc->used == 0 && block->malloc->size >= size) {
			if (block->malloc->last == 1)
			{
				block->unused_end_size = (block->unused_end_size + block->malloc->size) - size;
				block->malloc->size = size;
			}
			block->malloc->used = 1;
			return (block->malloc->ptr);
		}
		printf("UNUSED SPACE -> %zu\n", block->unused_end_size);
		printf("NEEDED SIZE -> %zu\n", size + sizeof(t_malloc));
		printf("FIRST CONDITION -> %i\n", block->malloc->last == 1);
		printf("SECOND CONDITION -> %i\n", block->unused_end_size >= size + sizeof(t_malloc));
		// size = ft_mem_align();
		if (block->malloc->last == 1 && block->unused_end_size >= size + sizeof(t_malloc))
		{
			block->unused_end_size = block->unused_end_size - (size + sizeof(t_malloc));
		printf("UNUSED SPACE AFTER -> %zu\n", block->unused_end_size);
			block->malloc->last = 0;
			block->malloc->next = block->malloc->ptr + block->malloc->size;
			block->malloc->next->used = 1;
			block->malloc->next->last = 1;
			block->malloc->next->size = size;
			block->malloc->next->ptr = (t_malloc *)block->malloc->next + 1;
			block->malloc->next->next = NULL;
			return (block->malloc->next->ptr);
		}
		block->malloc = block->malloc->next;
	}
	return (NULL);
}

void			*ft_malloc(size_t size)
{
	static int	init_lst = 0;
	void		*ptr;

	if (init_lst == 0)
	{
		lst_types.tiny = NULL;
		lst_types.small = NULL;
		lst_types.large = NULL;
		init_lst++;
	}
	ptr = ft_add_malloc(size);
	return (ptr);
}

int				main(void)
{
	char		*ptr;
	void		*ptr1;
	void		*ptr2;
	void		*ptr3;
	void		*ptr4;

	ptr = ft_malloc(6);
	// while (i < 102335) {
	// 	ptr[i] = 'a';
	// 	i++;
	// }
	ft_strcpy(ptr, "qwrer\0");
	ft_printf("%s\n", ptr);
	ft_printf("POINTEUR FINAL -> %p\n", ptr);

	ptr1 = ft_malloc(102170);
	ft_strcpy(ptr1, "ACECXD C\0");
	ft_printf("%s\n", ptr1);
	ft_printf("POINTEUR FINAL 1 -> %p\n", ptr1);

	ptr2 = ft_malloc(500);
	ft_strcpy(ptr2, "Y\0");
	ft_printf("%s\n", ptr2);
	ft_printf("POINTEUR FINAL 2 -> %p\n", ptr2);
	
	ptr3 = ft_malloc(3);
	ft_strcpy(ptr3, "YO\0");
	ft_printf("%s\n", ptr3);
	ft_printf("POINTEUR FINAL 3 -> %p\n", ptr3);

	ptr4 = ft_malloc(400);
	ft_strcpy(ptr4, "YOLOOOO\0");
	ft_printf("%s\n", ptr4);
	ft_printf("POINTEUR FINAL 4 -> %p\n", ptr4);

	return (0);
}

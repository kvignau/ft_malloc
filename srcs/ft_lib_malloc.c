#include "ft_malloc.h"

void		ft_free_empty(t_block *block, size_t type)
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
	if (!lst_types.large)
	{
		lst_types.large = ft_create_blocks(size + sizeof(t_malloc) + sizeof(t_block));
		if (!lst_types.large)
			return (NULL);
		return (lst_types.large->malloc->ptr);
	}
	block = lst_types.large;
	while (block->next)
		block = block->next;
	block->next = ft_create_blocks(size + sizeof(t_malloc) + sizeof(t_block));
	if (!block->next)
			return (NULL);
	block->next->prev = block;
	return (block->next->malloc->ptr);
}

void			*ft_add_small(size_t size)
{
	t_block		*block;
	void		*ptr;

	block = NULL;
	if (!lst_types.small)
	{
		lst_types.small = ft_create_blocks(SMALL);
		if (!lst_types.small)
			return (NULL);
		ptr = ft_find_space(lst_types.small, size);
		return (ptr);
	}
	block = lst_types.small;
	while (block)
	{
		block->malloc = block->first;
		if ((ptr = ft_find_space(block, size)))
			return ptr;
		if (block->last == 1)
			break;
		block = block->next;
	}
	block->last = 0;
	block->next = ft_create_blocks(SMALL);
	return (ft_find_space(block->next, size));
}

void			*ft_add_tiny(size_t size)
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
		return (ptr);
	}
	block = lst_types.tiny;
	while (block)
	{
		block->malloc = block->first;
		if ((ptr = ft_find_space(block, size)))
			return ptr;
		if (block->last == 1)
			break;
		block = block->next;
	}
	block->last = 0;
	block->next = ft_create_blocks(TINY);
	block->next->prev = block;
	return (ft_find_space(block->next, size));
}
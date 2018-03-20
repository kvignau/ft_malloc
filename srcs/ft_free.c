/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:16:15 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 12:16:17 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block			*ft_free_node(t_block *block, int *find)
{
	block->malloc->used = 0;
	(*find) = 1;
	return (block);
}

static int		ft_free_tiny(void *ptr)
{
	t_block		*tmp;
	int			find;
	int			i;

	find = 0;
	tmp = g_lst_types.tiny;
	while (tmp)
	{
		i = 0;
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->ptr == ptr)
				tmp = ft_free_node(tmp, &find);
			i += tmp->malloc->used;
			tmp->malloc = tmp->malloc->next;
		}
		if (find)
			break ;
		tmp = tmp->next;
	}
	if (!i)
		ft_free_empty(tmp, TINY);
	return (find);
}

static int		ft_free_small(void *ptr)
{
	t_block		*tmp;
	int			find;
	int			i;

	find = 0;
	tmp = g_lst_types.small;
	while (tmp)
	{
		i = 0;
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->ptr == ptr)
				tmp = ft_free_node(tmp, &find);
			i += tmp->malloc->used;
			tmp->malloc = tmp->malloc->next;
		}
		if (find)
			break ;
		tmp = tmp->next;
	}
	if (!i)
		ft_free_empty(tmp, SMALL);
	return (find);
}

static int		ft_free_large(void *ptr)
{
	t_block		*tmp;

	tmp = g_lst_types.large;
	while (tmp)
	{
		if (tmp->malloc->ptr == ptr)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				g_lst_types.large = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			munmap(tmp, tmp->malloc->size + sizeof(t_malloc) + sizeof(t_block));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (ft_free_tiny(ptr))
		return ;
	if (ft_free_small(ptr))
		return ;
	if (ft_free_large(ptr))
		return ;
}

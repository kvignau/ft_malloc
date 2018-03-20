/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:16:03 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 12:16:06 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*find_tiny_ptr(void *ptr, size_t size)
{
	t_block		*tmp;
	void		*save;

	tmp = g_lst_types.tiny;
	while (tmp)
	{
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->ptr == ptr)
			{
				if (tmp->malloc->size >= size)
					return (ptr);
				save = ft_malloc(size);
				save = ft_memcpy(save, tmp->malloc->ptr, tmp->malloc->size);
				ft_free(tmp->malloc->ptr);
				return (save);
			}
			tmp->malloc = tmp->malloc->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		*find_small_ptr(void *ptr, size_t size)
{
	t_block		*tmp;
	void		*save;

	tmp = g_lst_types.small;
	while (tmp)
	{
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->ptr == ptr)
			{
				if (tmp->malloc->size >= size)
					return (ptr);
				save = ft_malloc(size);
				save = ft_memcpy(save, tmp->malloc->ptr, tmp->malloc->size);
				ft_free(tmp->malloc->ptr);
				return (save);
			}
			tmp->malloc = tmp->malloc->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		*find_large_ptr(void *ptr, size_t size)
{
	t_block		*tmp;
	void		*save;

	tmp = g_lst_types.large;
	while (tmp)
	{
		tmp->malloc = tmp->first;
		while (tmp->malloc)
		{
			if (tmp->malloc->ptr == ptr)
			{
				if (tmp->malloc->size >= size)
					return (ptr);
				save = ft_malloc(size);
				save = ft_memcpy(save, tmp->malloc->ptr, tmp->malloc->size);
				ft_free(tmp->malloc->ptr);
				return (save);
			}
			tmp->malloc = tmp->malloc->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void			*ft_realloc(void *ptr, size_t size)
{
	void		*ret;

	ret = NULL;
	if (!ptr)
		return (ret);
	ret = find_tiny_ptr(ptr, size);
	if (!ret)
		ret = find_small_ptr(ptr, size);
	if (!ret)
		ret = find_large_ptr(ptr, size);
	return (ret);
}

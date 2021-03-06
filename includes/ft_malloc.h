/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:46:16 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/20 17:46:21 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include "../libft/includes/libft.h"

# define MAPS (MAP_ANON | MAP_PRIVATE)
# define PROTS (PROT_READ | PROT_WRITE)

# define SMALL getpagesize()
# define TINY (SMALL / 4)

typedef struct		s_malloc
{
	int				last;
	int				used;
	size_t			size;
	void			*ptr;
	struct s_malloc	*next;
}					t_malloc;

typedef struct		s_block
{
	size_t			unused_end_size;
	int				last;
	t_malloc		*malloc;
	t_malloc		*first;
	struct s_block	*next;
	struct s_block	*prev;
}					t_block;

typedef struct		s_alltypes
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_alltypes;

t_alltypes			g_lst_types;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

void				ft_free_empty(t_block *block, size_t type);
void				*ft_add_large(size_t size);
void				*ft_add_small(size_t size);
void				*ft_add_tiny(size_t size);
void				*ft_find_space(t_block *block, size_t size);
t_block				*crt_block(size_t type);
size_t				ft_align_memory(size_t size);

void				show_alloc_mem();

int					ft_free_tiny(void *ptr);
int					ft_free_small(void *ptr);
int					ft_free_large(void *ptr);

#endif

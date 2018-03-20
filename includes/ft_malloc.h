/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:17:02 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/23 19:25:36 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include "../ft_printf/includes/ft_printf.h"

// TO DELETE
# include <stdio.h>

# define MAPS (MAP_ANON | MAP_PRIVATE)
# define PROTS (PROT_READ | PROT_WRITE)

# define SMALL getpagesize()
# define TINY (SMALL / 4)

typedef struct 		s_malloc
{
	int				last;
	int				used;
	size_t			size;
	void			*ptr;
	struct s_malloc	*next;
	// struct s_malloc	*prev;
}					t_malloc;

typedef struct 	s_block
{
	size_t			unused_end_size;
	int				last;
	t_malloc		*malloc;
	t_malloc		*first;
	// TO TEST
	// t_malloc		*lastmalloc;
	struct s_block	*next;
	// struct s_block	*prev;
}					t_block;

typedef struct 	s_alltypes
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_alltypes;

t_alltypes			lst_types; 

void				free(void *ptr);
void				*ft_malloc(size_t size);
void				*realloc(void *ptr, size_t size);

void				*ft_find_space(t_block *malloc, size_t size);
void				*ft_add_malloc(size_t size);
t_block				*ft_create_blocks(size_t type);

#endif

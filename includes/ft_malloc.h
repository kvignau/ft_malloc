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
	void			*ptr;
	size_t			size;
	struct s_malloc	*next;
	struct s_malloc	*prev;
}					t_malloc;

typedef struct 	s_block
{
	size_t			unused_size;
	t_malloc		*malloc;
	struct s_block	*next;
	struct s_block	*prev;
}					t_block;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

#endif

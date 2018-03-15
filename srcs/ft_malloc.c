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

int			ft_create_blocks(t_block **block, size_t type) {
	// size_t		size;

	// size = type * 100 > sizeof(t_block *) ? type * 100 : sizeof(t_block *);
	(*block) = (t_block *)mmap(0, type * 100, PROTS, MAPS, -1, 0);
	if ((*block) == NULL)
	{
		return (-1);
	}

	(*block)->unused_size = type * 100 - (sizeof(t_block) + sizeof(t_malloc));
	(*block)->next = NULL;
	(*block)->prev = NULL;

	(*block)->malloc = (void *)(*block) + sizeof(t_block);
	(*block)->malloc->last = 1;
	(*block)->malloc->size = 0;
	(*block)->malloc->ptr = NULL;
	(*block)->malloc->next = NULL;
	(*block)->malloc->prev = NULL;

	return (0);
}

void			*malloc(size_t size)
{
	return (void*)size;
	// void		*str;

	// // str = (t_ *)mmap(0, size + 1, PROTS, MAPS, -1, 0);
	// // return (str);
}

// int				main(int ac, char **av)
int				main(void)
{
	int			i;
	// int			nb;
	// char		*str;

	t_block		*test;

	i = ft_create_blocks(&test, TINY);

	printf("RETRUN -> %d\n", i);

	printf("COUCOU -> %zu", test->unused_size);

	// if (ac != 2)
	// {
	// 	ft_putstr("Error\n");
	// 	return (0);
	// }	
	// nb = ft_atoi(av[1]);
	// str = (char *)malloc(nb);
	// printf("%p", str);
	// munmap(str, nb);
	// printf("%p", str);



	// if (ac != 3)
	// {
	// 	ft_putstr("Error\n");
	// 	return (0);
	// }
	// i = 0;
	// nb = ft_atoi(av[2]);

	// str = malloc(nb);
	// while (i < nb)
	// {
	// 	str[i] = av[1][0];
	// 	i++;
	// }
	// str[i] = '\0';
	// ft_putstr(str);


	// liberation de la memoire (address memoire, len)
	// munmap(str, nb);
	// ft_putstr(str);
	return (0);
}

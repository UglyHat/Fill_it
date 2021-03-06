/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpagot <rpagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:08:43 by rpagot            #+#    #+#             */
/*   Updated: 2017/05/10 14:34:10 by rolemass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fill_it.h"
#include <stdio.h>

static void			rinit_map(t_tetri *tetri)
{
	int i;

	i = 0;
	while (i < tetri->map_size)
	{
		tetri->map[i] = 0;
		i++;
	}
	i = 0;
	while (i < tetri->nb)
		tetri->pos[i++] = 0;
}

static void			ft_unmap_tetri(t_tetri *tetri, int i)
{
	int x;
	int y;

	x = tetri->pos[i] / 16;
	y = tetri->pos[i] % 16;
	tetri->map[x] ^= tetri->block[i].line1 >> y;
	tetri->map[x + 1] ^= tetri->block[i].line2 >> y;
	tetri->map[x + 2] ^= tetri->block[i].line3 >> y;
	tetri->map[x + 3] ^= tetri->block[i].line4 >> y;
	i++;
}

static int			ft_solve_tetri(t_tetri *tetri, int i, int size, int x)
{
	if (i >= tetri->nb)
		return (0);
	while (1)
	{
		if (x > 0 && (((tetri->range[i]) + (x % 16) - 1) == tetri->map_size))
		{
			x = (x / 16) * 16 + 16;
		}
		if ((x + tetri->range[i]) >= size)
			return (-1);
		if (ft_test_tetri(tetri, i, x) == 0)
		{
			if (ft_solve_tetri(tetri, i + 1, size, 0) == 0)
				return (0);
			ft_unmap_tetri(tetri, i);
		}
		x++;
	}
}

int					ft_test_by_size(t_tetri *tetri)
{
	int size;

	while (1)
	{
		size = tetri->map_size * 16;
		rinit_map(tetri);
		if (ft_solve_tetri(tetri, 0, size, 0) == 0)
		{
			ft_memdel((void**)&tetri->block);
			ft_memdel((void**)&tetri->range);
			return (size);
		}
		tetri->map_size++;
	}
	return (-1);
}

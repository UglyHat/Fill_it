/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_and_stock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolemass <rolemass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:31:59 by rolemass          #+#    #+#             */
/*   Updated: 2017/05/03 07:26:55 by rolemass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fill_it.h"
#include <stdio.h>

static void				ft_init_map(t_tetri *tetri)
{
	int n;

	n = 0;
	if (!(tetri->map = (unsigned short *)malloc(16 * sizeof(unsigned short)))
		|| !(tetri->pos = (short*)malloc(sizeof(short) * tetri->nb))
		|| !(tetri->block = (t_block*)malloc(sizeof(t_block) * tetri->nb))
		|| !(tetri->range = (unsigned short*)malloc(sizeof(unsigned short) * tetri->nb)))
		exit(1);
	while (++n < 16)
		tetri->map[n] = 0;
	n = 0;
	while (n < tetri->nb)
	{
		tetri->range[n] = 0;
		tetri->block[n] = ft_split_short(tetri->block, n, tetri->tetri[n]);
		n++;
	}
	ft_get_tetris_range(tetri);
	n = 0;
	while (n < tetri->nb)
		tetri->pos[n++] = -1;
}

static unsigned short	ft_convert_to_short(char *buff)
{
	unsigned short	shape;
	size_t			i;

	shape = 0;
	i = 0;
	while (i != 20)
	{
		if (buff[i] == '#')
			shape += (1 << (15 - i + (i / 5)));
		++i;
	}
	return (shape);
}

static unsigned short	ft_check_one(char *buff, t_tetri *tetri)
{
	size_t			i;

	i = 0;
	while (buff[i])
	{
		if ((i + 1) % 5 == 0 && buff[i] != '\n')
			return (0);
		++i;
	}
	*tetri->tetri = ft_convert_to_short(buff);
	if ((*tetri->tetri = ft_check_if_valid(tetri)) == 0)
		return (0);
	return (*tetri->tetri);
}

int						ft_read_fd(int fd, t_tetri *tetri)
{
	int				ret;
	char			*buff;

	if (!(buff = ft_strnew(BUF_SIZE)) || fd < 0)
	{
	ft_putendl("invalid fd");
	  exit(EXIT_FAILURE);
	}
	while ((ret = read(fd, buff, BUF_SIZE)) > 0)
	{
		if ((*(tetri->tetri) = ft_check_one(buff, tetri)) == 0)
			exit(EXIT_FAILURE);
		tetri->tetri++;
		tetri->nb++;
	}
	tetri->tetri -= tetri->nb;
	ft_init_map(tetri);
	tetri->map_size = ft_sqrt(tetri->area);
	// tetri->map_size = ft_sqrt(tetri->nb * 4);
	ft_test_by_size(tetri);
	ft_final_display(tetri);
	ft_memdel((void **)&buff);
	return (ret);
}

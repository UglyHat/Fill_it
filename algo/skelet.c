/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skelet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolemass <rolemass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 02:06:59 by rolemass          #+#    #+#             */
/*   Updated: 2016/12/25 02:16:42 by rolemass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fill_it.h"


static t_mlist	init_map(t_mlist *list, unsigned short *map)
{
	t_mlist *new;

	if ((new = (m_list*)malloc(sizeof(m_list))) == NULL)
		return (NULL);
	if (!(new->content = (unsigned short*)malloc(sizeof(unsigned short *))))
		return (NULL);
	new->content = map;
	new->next = NULL;
	new->prev = list;
	return(new);
}

static t_dlist	*ft_mlist_take_at(t_dlist list, int at)
{
	int	i;

	i = 0;
	while(list && i < at)
	{
		list = list->next;
		i++;
	}
	return (list);
}

unsigned short	*test_tri(t_dlist *tetri, t_mlist *map_lst)
{
	unsigned short *tmp;
	int				i;
	int				j;

	i = 0;
	j = 0;
	tmp = map_lst;
	while (i < 4)
	{
		if ((j = cmp_tetri_one(tetri, map_lst[tetri->prev->pos])) == -1)
			return (NULL);
		if ((j = cmp_tetri_two(tetri, map_lst[tetri->prev->pos + 1], j)) == -1)
			return (NULL);
		if ((j = cmp_tetri_three(tetri, map_lst[tetri->prev->pos + 2], j)) == -1)
			return (NULL);
		if ((cmp_tetri_four(tetri, map_lst[tetri->prev->pos + 3]) == -1))
			return (NULL);
	}
	else
		map_lst = add_tetri_to_map(tetri, map_lst);
	return (map_lst);
}

unsigned short	*skelet(unsigned short *map, t_dlist *list)
{
	t_mlist			*map_lst;
	int				i;
	unsigned short	*tmp;

	i = 0;
	map_lst->content = map;
	if (!(map_lst = ft_init_head(map_lst)))
		return (NULL);
	while (isntvalid())
	{
		if ((tmp = test_tri(list, map_lst)) == NULL && list->next == head)
		{
			map_lst = map_lst->prev;
			list = ft_mlist_take_at(list, map_lst->last + 1);
		}
		if (tmp != NULL)
			if (!(map_lst->next = init_map(map_lst, tmp)) && list->status = 1)
				return (NULL);
			map_lst = map_lst->next;
		list = list->next;
	}
}
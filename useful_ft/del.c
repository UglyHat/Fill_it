/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolemass <rolemass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 04:33:30 by rolemass          #+#    #+#             */
/*   Updated: 2017/03/15 04:37:43 by rolemass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_del_tetri(t_tetri **tetri)
{
	int i;

	while(i < 23)
	{
		if (*tetri[i])
		{
			free(*tetri[i]->l);
			free(*tetri[i]);
		}
		i++;
	}
}
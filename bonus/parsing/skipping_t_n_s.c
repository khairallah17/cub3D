/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_t_n_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:27:01 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 20:31:23 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_isspace(int c)
{
	return (((8 < c) && (c < 14)) || (c == 32));
}

int	ft_isline(char c)
{
	return ((c == '\r') || (c == '\n'));
}

int	ft_isstab(int c)
{
	return ((c == 9) || (c == 32));
}

void	fill_map_body(t_map3d *map)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (1)
	{
		x = 0;
		c = 1;
		while (1)
		{
			ft_mapreadch(map, &c);
			if ((c == '\0') || (c == '\n'))
				break ;
			map->map1d[y * map->width + x++] = c;
		}
		while (x < map->width)
			map->map1d[y * map->width + x++] = ' ';
		if (c == '\0')
			break ;
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:22:00 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 20:22:15 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_extcmp(const char *file, const char *ext)
{
	int	p;
	int	i;
	int	k;

	p = 0;
	i = 0;
	k = 0;
	while (ext && ext[k])
		k++;
	while (file && file[i])
	{
		if (file[i] == '/')
			p = i + 1;
		i++;
	}
	if ((k < 2) || (i - p < 3) || (i - p <= k)
		|| (file[p] == '.') || (ft_strncmp(file + i - k, ext, k) != 0))
		return (0);
	return (1);
}

void	map_error(const char *msgerr)
{
	close(getmap()->fd);
	free(getmap()->map1d);
	write(2, msgerr, ft_strlen(msgerr));
	write(2, "\n", 1);
	exit (EXIT_FAILURE);
}

char	map_get10(int x, int y)
{
	t_map3d	*map;

	map = getmap();
	if ((x < 0) || (y < 0) || (x >= map->width) || (y >= map->height))
		return (' ');
	return (map->map1d[y * map->width + x]);
}

void	is_surrounded_by_spaces(int x, int y)
{
	if (ft_strchr("NEWS0", map_get10(x, y)))
	{
		if (map_get10(x - 1, y + 0) == ' ')
			map_error("invalid map!");
		if (map_get10(x + 1, y + 0) == ' ')
			map_error("invalid map!");
		if (map_get10(x - 0, y + 1) == ' ')
			map_error("invalid map!");
		if (map_get10(x - 0, y - 1) == ' ')
			map_error("invalid map!");
	}
}

void	map_check(t_map3d *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			is_surrounded_by_spaces(x, y);
			if (ft_strchr("NEWS", map_get10(x, y)))
			{
				getmap()->player_x = x + 0.5;
				getmap()->player_y = y + 0.5;
				if (map_get10(x, y) == 'N')
					map->player_angle = M_PI * 1.5;
				if (map_get10(x, y) == 'W')
					map->player_angle = M_PI * 1.0;
				if (map_get10(x, y) == 'S')
					map->player_angle = M_PI * 0.5;
			}
		}
	}
}

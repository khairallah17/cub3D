/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_mapsize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:25:53 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 20:26:07 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	read_map_body(t_map3d *map)
{
	char	c;
	int		i;

	map->map1d = malloc(map->width * map->height + 1);
	if (!map->map1d)
		map_error("can't allocate memory!");
	map->map1d[map->width * map->height] = 0;
	close(getmap()->fd);
	getmap()->fd = open(map->filename, O_RDONLY);
	i = 0;
	while ((i < map->bodystart) && (read(getmap()->fd, &c, 1) == 1))
		i++;
	fill_map_body(map);
	map_check(map);
	close(getmap()->fd);
}

void	update_map_width(t_map3d *map, int *first_index, int *last_index)
{
	int	len;

	len = *last_index - *first_index;
	if (((map->width > 0) && (len < 1)) || (map->players > 1))
		map_error("invalid map!");
	if (map->width < len)
		map->width = len;
	*first_index = map->offset;
	*last_index = map->offset;
	if (map->width == 0)
		map->bodystart = map->offset;
	if (map->width)
		map->height++;
}

void	getmapsize(t_map3d *map)
{
	char	c;
	int		first_index;
	int		last_index;

	first_index = map->offset;
	last_index = map->offset;
	map->bodystart = map->offset;
	c = 1;
	map->players = 0;
	while (c != '\0')
	{
		ft_mapreadch(map, &c);
		if (!ft_strchr("01 NSEW\n", c))
			map_error("invalid map character!");
		map->players += ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'));
		if (c && !ft_isspace(c))
			last_index = map->offset;
		if ((c == '\n') || (c == '\0'))
			update_map_width(map, &first_index, &last_index);
	}
}

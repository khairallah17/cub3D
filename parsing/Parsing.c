/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:30:25 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 20:31:16 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <libc.h>

t_map3d	*getmap(void)
{
	static t_map3d	map;

	return (&map);
}

void	open_cubfile(char *cubfile)
{
	if (ft_extcmp(cubfile, ".cub") == 0)
		map_error("Error: In Map Reading it should be <MAP_NAME.CUB>");
	getmap()->filename = cubfile;
	getmap()->fd = open(cubfile, O_RDONLY);
	if (getmap()->fd < 0)
		map_error("Error: can't open file!");
}

void	map_load_files(char c, t_map3d	*map)
{
	if (((c == 'N') && ((ft_mapreadch(map, &c) != 1) || (c != 'O')
				|| (ft_copypath(map, map->north, &c) == -1)))
		|| ((c == 'E') && ((ft_mapreadch(map, &c) != 1)
				|| (c != 'A') || (ft_copypath(map, map->east, &c) == -1)))
		|| ((c == 'W') && ((ft_mapreadch(map, &c) != 1) || (c != 'E')
				|| (ft_copypath(map, map->west, &c) == -1)))
		|| ((c == 'S') && ((ft_mapreadch(map, &c) != 1)
				|| (c != 'O') || (ft_copypath(map, map->south, &c) == -1))))
		map_error("invalid path!");
}

void	map_load(char *cubfile)
{
	char	c;
	t_map3d	*map;

	open_cubfile(cubfile);
	map = getmap();
	while (ft_mapreadch(map, &c) == 1)
	{
		ft_skipcharset(map, &c, " \t\r\v\f\n");
		if ((c == 'F') && (ft_copycolor(map, &map->floor, &c) == -1))
			map_error("invalid floor color!");
		if ((c == 'C') && (ft_copycolor(map, &map->ceiling, &c) == -1))
			map_error("invalid ceiling color!");
		map_load_files(c, map);
		if (map->flags_number == MAX_FLAGS_NUMBER)
		{
			getmapsize(map);
			if ((map->width < 3) || (map->height < 3) || (map->players != 1))
				map_error("invalid map!");
			return (read_map_body(map));
		}
	}
	map_error("can't read all components!");
}

t_cub3d	*cub3d_parsing(int ac, char **av)
{
	static t_cub3d	cub;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit (EXIT_FAILURE);
	}
	map_load(av[1]);
	getmap()->player_speed = DEFAULT_PLAYER_SPEED;
	getmap()->player_rotation_angle = DEFAULT_PLAYER_ROTATION_ANGLE;
	return (&cub);
}

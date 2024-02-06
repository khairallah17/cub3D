/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/06 20:11:07 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	wall_collision(t_global_conf *config, float x, float y)
{
	int	minimap_height;
	int	minimap_width;
	int	px;
	int	py;

	minimap_height = getmap()->height * MINIMAP_SCALE;
	minimap_width = getmap()->width * MINIMAP_SCALE;
	px = getmap()->player_x;
	py = getmap()->player_y;
	if (x < 0 || (int)x >= minimap_width || y < 0 || (int)y >= minimap_height)
		return (0);
	if ((map_get10(py, (int)(x)) == '1' \
		&& map_get10((int)(y), px) == '1'))
		return (1);
	return ((map_get10(x, y) == '1') || (map_get10(x, y) == ' '));
}

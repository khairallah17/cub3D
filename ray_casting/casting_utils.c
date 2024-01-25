/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:12:18 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:23:34 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	correct_angle(double ray_angle)
{
	ray_angle = remainder(ray_angle, M_PI * 2);
	if (ray_angle < 0)
	{
		ray_angle += M_PI * 2;
	}
	return (ray_angle);
}

double	calculating_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	wall_hit_checker(double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || (int)x >= MINIMAP_WIDTH || y < 0 || (int)y >= MINIMAP_HEIGHT)
		return (1);
	map_x = x / MINIMAP_SCALE;
	map_y = y / MINIMAP_SCALE;
	return (map[mapGridIndexY][mapGridIndexX] == '1');
}

void	cast_all_rays(t_global_conf *config)
{
	double	ray_angle;
	int		i;

	ray_angle = config->player->rotation_angle - (FOV / 2);
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		cast_ray(config, ray_angle, i);
		draw_rays(config, i);
		ray_angle += FOV / NUM_OF_RAYS;
		i++;
	}
}

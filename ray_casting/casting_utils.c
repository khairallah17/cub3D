/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:12:18 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/05 00:09:02 by mkhairal         ###   ########.fr       */
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

int	wall_hit_checker(t_global_conf *config, double x, double y)
{
	int	map_x;
	int	map_y;
	int	minimap_height;
	int	minimap_width;

	minimap_height = config->cub->prs_map.map.height * MINIMAP_SCALE;
	minimap_width = config->cub->prs_map.map.width * MINIMAP_SCALE;
	if (x < 0 || (int)x >= minimap_width || y < 0 || (int)y >= minimap_height)
		return (1);
	map_x = x / (double)MINIMAP_SCALE;
	map_y = y / (double)MINIMAP_SCALE;
	return (config->cub->prs_map.map.map_grid[map_y][map_x] == '1');
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
		cast_ray(config, ray_angle, i);
		// draw_rays(config, i);
		render_3d(config, i);
		ray_angle += (double)FOV / (double)NUM_OF_RAYS;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:12:18 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/06 23:03:41 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_double	correct_angle(t_double ray_angle)
{
	ray_angle = remainder(ray_angle, M_PI * 2);
	if (ray_angle < 0)
	{
		ray_angle += M_PI * 2;
	}
	return (ray_angle);
}

t_double	calculating_distance(t_double x1, t_double y1, \
			t_double x2, t_double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_double	normalize_angle(t_double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	do_cast(t_global_conf *config, int rayindex, t_double angle)
{
	t_double	x;
	t_double	y;
	t_double	dda;

	dda = 0.0;
	while (1)
	{
		x = getmap()->player_x + dda * cos(angle);
		y = getmap()->player_y + dda * sin(angle);
		if (wall_collision(NULL, x, y))
		{
			t_double vx = (int)x + (cos(angle) < 0);
			t_double vy = getmap()->player_y + (tan(angle) * (vx - getmap()->player_x));

			t_double hy = (int)y + (sin(angle) < 0);
			t_double hx = getmap()->player_x + ((hy -  getmap()->player_y) / tan(angle));

			config->rays[rayindex].wall_hit_x = hx * TILE;
			config->rays[rayindex].wall_hit_y = hy * TILE;
			config->rays[rayindex].distance   = calculating_distance(hx, hy,  getmap()->player_x,  getmap()->player_y);
			if (
				calculating_distance(vx, vy,  getmap()->player_x,  getmap()->player_y) <
				config->rays[rayindex].distance
			)
			{
				config->rays[rayindex].wall_hit_x = vx * TILE;
				config->rays[rayindex].wall_hit_y = vy * TILE;
				config->rays[rayindex].distance   = calculating_distance(vx, vy,  getmap()->player_x,  getmap()->player_y);
			}
			config->rays[rayindex].distance *= TILE;
			break;
			// exit(0);
		}
		dda += 0.8;
	}

	// exit(0);
}

void	cast_all_rays(t_global_conf *config)
{
	t_double	ray_angle;
	int			i;

	draw_map(config);
	ray_angle = getmap()->player_angle - (FOV / 2);
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		// do_cast(config, i, ray_angle);
		cast_ray(config, ray_angle, i);
		draw_rays(config, i);
		// cast_ray(config, ray_angle, i);
		// render_3d(config, i);
		ray_angle += (t_double)FOV / (t_double)NUM_OF_RAYS;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:12:18 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 22:24:30 by eagoumi          ###   ########.fr       */
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

void	cast_all_rays(t_global_conf *config)
{
	t_double	ray_angle;
	int			i;

	ray_angle = getmap()->player_angle - (to_rad(FOV) / 2);
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		cast_ray(config, ray_angle, i);
		render_3d(config, i);
		ray_angle += (t_double)to_rad(FOV) / (t_double)NUM_OF_RAYS;
		i++;
	}
}

t_double	to_rad(t_double angle)
{
	return (angle * (M_PI / 180));
}

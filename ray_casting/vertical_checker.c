/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:42:05 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/06 22:44:30 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculating_vertical_distances(t_global_conf *config, \
										t_ray_info *ray_info)
{
	while ((ray_info->next_vertical_hit_x >= 0 \
	&& ray_info->next_vertical_hit_x <= \
	getmap()->width * MINIMAP_SCALE) \
	&& (ray_info->next_vertical_hit_y >= 0 \
	&& ray_info->next_vertical_hit_y <= \
	getmap()->height * MINIMAP_SCALE))
	{
		ray_info->x_check = ray_info->next_vertical_hit_x;
		if (ray_info->ray_facing_left)
			ray_info->x_check -= 1;
		ray_info->y_check = ray_info->next_vertical_hit_y;
		if (wall_collision(config, ray_info->x_check / MINIMAP_SCALE, \
				ray_info->y_check / MINIMAP_SCALE))
		{
			ray_info->vertical_wall_hit = 1;
			ray_info->vertical_wall_hit_x = ray_info->next_vertical_hit_x;
			ray_info->vertical_wall_hit_y = ray_info->next_vertical_hit_y;
			break ;
		}
		else
		{
			ray_info->next_vertical_hit_x += ray_info->x_step;
			ray_info->next_vertical_hit_y += ray_info->y_step;
		}
	}
}

void	vertical_casting(t_global_conf *config, t_ray_info *ray_info)
{
	ray_info->x_inter = floor((getmap()->player_x)) * (t_double)MINIMAP_SCALE;
	if (ray_info->ray_facing_right)
		ray_info->x_inter += (t_double)MINIMAP_SCALE;
	ray_info->y_inter = getmap()->player_y * MINIMAP_SCALE + \
		(ray_info->x_inter - getmap()->player_x * MINIMAP_SCALE) \
			* tan(ray_info->ray_angle);
	ray_info->x_step = (t_double)MINIMAP_SCALE;
	if (ray_info->ray_facing_left)
		ray_info->x_step *= -1;
	ray_info->y_step = (t_double)MINIMAP_SCALE * tan(ray_info->ray_angle);
	if (ray_info->ray_facing_up && ray_info->y_step > 0)
		ray_info->y_step *= -1;
	if (ray_info->ray_facing_down && ray_info->y_step < 0)
		ray_info->y_step *= -1;
	ray_info->next_vertical_hit_x = ray_info->x_inter;
	ray_info->next_vertical_hit_y = ray_info->y_inter;
	calculating_vertical_distances(config, ray_info);
}

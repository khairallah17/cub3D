/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:42:05 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 14:51:58 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculating_vertical_distances(t_ray_info *ray_info)
{
	while ((ray_info->next_vertical_hit_x >= 0 \
		&& ray_info->next_vertical_hit_x <= (MINIMAP_WIDTH)) \
		&& (ray_info->next_vertical_hit_y >= 0 \
		&& ray_info->next_vertical_hit_y <= MINIMAP_HEIGHT))
	{
		ray_info->x_check = ray_info->next_vertical_hit_x;
		if (ray_info->is_ray_facing_left)
			ray_info->x_check -= 1;
		ray_info->y_check = ray_info->next_vertical_hit_y;
		if (wall_hit_checker(ray_info->x_check, ray_info->y_check))
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

void	vertical_casting(t_ray_info *ray_info)
{
	ray_info->x_inter = floor((config->player->x) \
		/ MINIMAP_SCALE) * MINIMAP_SCALE;
	if (ray_info->is_ray_facing_right)
		ray_info->x_inter = MINIMAP_SCALE;
	ray_info->y_inter = config->player->y + \
		(ray_info->x_inter - config->player->x) * tan(ray_info->ray_angle);
	ray_info->x_step = MINIMAP_SCALE;
	if (ray_info->is_ray_facing_left)
		ray_info->x_step *= -1;
	ray_info->y_step = MINIMAP_SCALE * tan(ray_info->ray_angle);
	if (ray_info->is_ray_facing_up && ray_info->y_step > 0)
		ray_info->y_step *= -1;
	if (ray_info->is_ray_facing_down && ray_info->y_step < 0)
		ray_info->y_step *= -1;
	calculating_vertical_distances(ray_info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:41:11 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/26 16:11:15 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculating_horizontal_distances(t_global_conf *config, \
											t_ray_info *ray_info)
{
	while ((ray_info->next_horizontal_hit_x >= 0 \
	&& ray_info->next_horizontal_hit_x <= \
	config->cub->prs_map.map.height * MINIMAP_SCALE) \
	&& (ray_info->next_horizontal_hit_y >= 0 \
	&& ray_info->next_horizontal_hit_y <= \
	config->cub->prs_map.map.width * MINIMAP_SCALE))
	{
		ray_info->x_check = ray_info->next_horizontal_hit_x;
		ray_info->y_check = ray_info->next_horizontal_hit_y;
		if (ray_info->ray_facing_up)
			ray_info->y_check -= 1;
		if (wall_hit_checker(config, ray_info->x_check, ray_info->y_check))
		{
			ray_info->horizontal_wall_hit = 1;
			ray_info->horizontal_wall_hit_x = ray_info->next_horizontal_hit_x;
			ray_info->horizontal_wall_hit_y = ray_info->next_horizontal_hit_y;
			break ;
		}
		else
		{
			ray_info->next_horizontal_hit_x += ray_info->x_step;
			ray_info->next_horizontal_hit_y += ray_info->y_step;
		}
	}
}

void	horizontal_casting(t_global_conf *config, t_ray_info *ray_info)
{
	ray_info->next_horizontal_hit_x = ray_info->x_inter;
	ray_info->next_horizontal_hit_y = ray_info->x_inter;
	ray_info->y_inter = \
		floor((config->player->y) / MINIMAP_SCALE) * MINIMAP_SCALE;
	if (ray_info->ray_facing_down)
		ray_info->y_inter = MINIMAP_SCALE;
	ray_info->x_inter = \
		config->player->x + ((ray_info->y_inter - config->player->y) \
								/ tan(ray_info->ray_angle));
	ray_info->y_step = MINIMAP_SCALE;
	if (ray_info->ray_facing_up)
		ray_info->ray_facing_up *= -1;
	ray_info->x_step = MINIMAP_SCALE / tan(ray_info->ray_angle);
	if (ray_info->ray_facing_left && ray_info->x_step > 0)
		ray_info->x_step *= -1;
	else if (ray_info->ray_facing_right && ray_info->x_step < 0)
		ray_info->x_step *= -1;
	calculating_horizontal_distances(config, ray_info);
}

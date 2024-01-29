/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:50:39 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/28 23:03:53 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ray_casting_setup(t_ray_info *ray_info, double ray_angle)
{
	ray_info->ray_angle = correct_angle(ray_angle);
	if (ray_info->ray_angle > 0 && ray_info->ray_angle < M_PI)
		ray_info->ray_facing_down = 1;
	if (ray_info->ray_angle < 0.5 * M_PI || ray_info->ray_angle > 1.5 * M_PI)
		ray_info->ray_facing_right = 1;
	ray_info->ray_facing_up = !ray_info->ray_facing_down;
	ray_info->ray_facing_left = !ray_info->ray_facing_right;
}

void	ray_distance_assignement(t_global_conf *config, \
			t_ray_info *ray_info, int pos)
{
	if (ray_info->horizontal_wall_hit)
		ray_info->horizontal_distance = calculating_distance(config->player->x, \
		config->player->y, ray_info->horizontal_wall_hit_x, \
		ray_info->horizontal_wall_hit_y);
	else
		ray_info->horizontal_distance = INT_MAX;
	if (ray_info->vertical_wall_hit)
		ray_info->vertical_distance = calculating_distance(config->player->x, \
		config->player->y, ray_info->vertical_wall_hit_x, \
		ray_info->vertical_wall_hit_y);
	else
		ray_info->vertical_distance = INT_MAX;
	if (ray_info->vertical_distance < ray_info->horizontal_distance)
	{
		config->rays[pos].distance = ray_info->vertical_distance;
		config->rays[pos].wall_hit_x = ray_info->vertical_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->vertical_wall_hit_y;
		config->rays[pos].was_hit_vertical = 1;
	}
	else
	{
		config->rays[pos].distance = ray_info->horizontal_distance;
		config->rays[pos].wall_hit_x = ray_info->horizontal_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->horizontal_wall_hit_y;
		config->rays[pos].was_hit_vertical = 0;
	}
	config->rays[pos].ray_angle = ray_info->ray_angle;
	config->rays[pos].ray_facing_down = ray_info->ray_facing_down;
	config->rays[pos].ray_facing_up = ray_info->ray_facing_up;
	config->rays[pos].ray_facing_left = ray_info->ray_facing_left;
	config->rays[pos].ray_facing_right = ray_info->ray_facing_right;
}

void	cast_ray(t_global_conf *config, double ray_angle, int pos)
{
	t_ray_info	ray_info;

	init_ray(&ray_info);
	ray_casting_setup(&ray_info, ray_angle);
	config->player->y *= (double)MINIMAP_SCALE;
	config->player->x *= (double)MINIMAP_SCALE;
	horizontal_casting(config, &ray_info);
	vertical_casting(config, &ray_info);
	ray_distance_assignement(config, &ray_info, pos);
	config->player->y /= (double)MINIMAP_SCALE;
	config->player->x /= (double)MINIMAP_SCALE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:50:39 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 22:22:15 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <limits.h>

void	ray_casting_setup(t_ray_info *ray_info, t_double ray_angle)
{
	ray_info->ray_angle = ray_angle;
	ray_info->ray_facing_left = 0;
	ray_info->ray_facing_right = 0;
	ray_info->ray_facing_up = 0;
	ray_info->ray_facing_down = 0;
	if ((0 <= ray_angle) && (ray_angle < M_PI_2))
	{
		ray_info->ray_facing_down = 1;
		ray_info->ray_facing_right = 1;
	}
	else if ((M_PI_2 <= ray_angle) && (ray_angle < M_PI))
	{
		ray_info->ray_facing_down = 1;
		ray_info->ray_facing_left = 1;
	}
	else if ((M_PI <= ray_angle) && (ray_angle < 3 * M_PI_2))
	{
		ray_info->ray_facing_up = 1;
		ray_info->ray_facing_left = 1;
	}
	else if (3 * M_PI_2 <= ray_angle)
	{
		ray_info->ray_facing_up = 1;
		ray_info->ray_facing_right = 1;
	}
}

void	ray_distance_assignement_1(t_ray_info *ray_info)
{
	if (ray_info->horizontal_wall_hit)
		ray_info->horizontal_distance = \
		calculating_distance(getmap()->player_x * MINIMAP_SCALE, \
		getmap()->player_y * MINIMAP_SCALE, ray_info->horizontal_wall_hit_x, \
		ray_info->horizontal_wall_hit_y);
	else
		ray_info->horizontal_distance = (float)INT_MAX;
	if (ray_info->vertical_wall_hit)
		ray_info->vertical_distance = \
		calculating_distance(getmap()->player_x * MINIMAP_SCALE, \
		getmap()->player_y * MINIMAP_SCALE, ray_info->vertical_wall_hit_x, \
		ray_info->vertical_wall_hit_y);
	else
		ray_info->vertical_distance = (float)INT_MAX;
}

void	ray_distance_assignement_3(t_global_conf *config, \
				t_ray_info *ray_info, int pos)
{
	config->rays[pos].ray_angle = ray_info->ray_angle;
	config->rays[pos].ray_facing_down = ray_info->ray_facing_down;
	config->rays[pos].ray_facing_up = ray_info->ray_facing_up;
	config->rays[pos].ray_facing_left = ray_info->ray_facing_left;
	config->rays[pos].ray_facing_right = ray_info->ray_facing_right;
}

void	ray_distance_assignement(t_global_conf *config, \
			t_ray_info *ray_info, int pos)
{
	ray_distance_assignement_1(ray_info);
	if (ray_info->vertical_distance < ray_info->horizontal_distance)
	{
		config->rays[pos].distance = ray_info->vertical_distance;
		config->rays[pos].wall_hit_x = ray_info->vertical_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->vertical_wall_hit_y;
		config->rays[pos].was_hit_vertical = 1;
		if (config->rays[pos].ray_facing_right)
			config->rays[pos].texture = config->txt_load_png.right_east;
		else
			config->rays[pos].texture = config->txt_load_png.left_west;
	}
	else
	{
		config->rays[pos].distance = ray_info->horizontal_distance;
		config->rays[pos].wall_hit_x = ray_info->horizontal_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->horizontal_wall_hit_y;
		config->rays[pos].was_hit_vertical = 0;
		if (config->rays[pos].ray_facing_up)
			config->rays[pos].texture = config->txt_load_png.up_north;
		else
			config->rays[pos].texture = config->txt_load_png.down_south;
	}
	ray_distance_assignement_3(config, ray_info, pos);
}

void	cast_ray(t_global_conf *config, t_double ray_angle, int pos)
{
	t_ray_info	ray_info;

	init_ray(&ray_info);
	ray_casting_setup(&ray_info, ray_angle);
	horizontal_casting(config, &ray_info);
	vertical_casting(config, &ray_info);
	ray_distance_assignement(config, &ray_info, pos);
	ray_distance_assignement(config, &ray_info, pos);
}

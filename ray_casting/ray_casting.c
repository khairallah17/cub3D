/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:50:39 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 15:45:00 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_ray_info	*ray_casting_setup(double ray_angle)
{
	t_ray_info	ray_info;

	if (ray_angle > 0 && ray_angle < M_PI)
		ray_info.is_ray_facing_down = 0;
	else if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
		ray_info.is_ray_facing_right = 1;
	ray_info.is_ray_facing_up = !ray_info.is_ray_facing_down;
	ray_info.is_ray_facing_left = !ray_info.is_ray_facing_right;
	ray_info = ray_angle;
	return (&ray_info);
}

void	ray_distance_assignement(t_global_conf *config, t_ray_info *ray_info, int pos)
{
	double	horizontal_distance;
	double	vertical_distance;

	horizontal_distance = INT_MAX;
	vertical_distance = INT_MAX;
	if (ray_info->horizontal_wall_hit)
		horizontal_distance = calculating_distance(config->player->x, \
		config->player->y, ray_info->horizontal_wall_hit_x, \
		ray_info->horizontal_wall_hit);
	else if (ray_info->vertical_wall_hit)
		vertical_distance = calculating_distance(config->player->x, \
		config->player->y, ray_info->vertical_wall_hit_x, \
		ray_info->vertical_wall_hit);
	if (vertical_distance < horizontal_distance)
	{
		config->rays[pos].distance = vertical_distance;
		config->rays[pos].wall_hit_x = ray_info->vertical_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->vertical_wall_hit_y;
		config->rays[pos].was_hit_vertical = 1;
	}
	else
	{
		config->rays[pos].distance = horizontal_distance;
		config->rays[pos].wall_hit_x = ray_info->horizontal_wall_hit_x;
		config->rays[pos].wall_hit_y = ray_info->horizontal_wall_hit_y;
		config->rays[pos].was_hit_vertical = 0;
	}
}

void	cast_ray(t_global_conf *config, double ray_angle, int pos)
{
	t_ray_info	ray_info;

	ray_info = ray_casting_setup(ray_angle);
	ray_angle = correct_angle(ray_angle);
	config->player->y *= MINMAP_SCALE;
	config->player->x *= MINMAP_SCALE;
	horizontal_casting(config, ray_info);
	calculating_horizontal_distances(ray_info);
	vertical_casting(config, ray_info);
	calculating_vertical_distances(ray_info);
	ray_distance_assignement(config, ray_info, pos);
}

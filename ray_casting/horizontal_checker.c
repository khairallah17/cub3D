/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:41:11 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/28 23:04:17 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculating_horizontal_distances(t_global_conf *config, \
											t_ray_info *ray_info)
{
	while ((ray_info->next_horizontal_hit_x >= 0 \
	&& ray_info->next_horizontal_hit_x <= \
	(getmap()->width * MINIMAP_SCALE)) \
	&& (ray_info->next_horizontal_hit_y >= 0 \
	&& ray_info->next_horizontal_hit_y <= \
	getmap()->height * MINIMAP_SCALE))
	{
		ray_info->x_check = ray_info->next_horizontal_hit_x;
		ray_info->y_check = ray_info->next_horizontal_hit_y;
		if (ray_info->ray_facing_up)
			ray_info->y_check -= 1;
		if (wall_collision(config, ray_info->x_check / MINIMAP_SCALE, ray_info->y_check / MINIMAP_SCALE))
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

void    draw_single_line(t_global_conf *config) {

    t_double dx;
    t_double dy;
    t_double px;
    t_double py;
    t_double tmp;

    px = getmap()->player_x * MINIMAP_SCALE;
    py = getmap()->player_y * MINIMAP_SCALE;
    dx = (64 * cos(getmap()->player_angle) + px); // assuming px and py are the (0, 0);
    dy = (64 * sin(getmap()->player_angle) + py);

    t_double slope = (py - dy) / (px - dx);
    t_double y_intercept = py - slope * px; // py = slope * px + t_intercept

    if (px >= dx)
    {
        tmp = px;
        px = dx;
        dx = tmp;
    }
    while (px <= dx)
    {
        mlx_put_pixel(config->img,  px, slope * px + y_intercept, 0x008000FF);
        px +=0.1;
    }

}

void	horizontal_casting(t_global_conf *config, t_ray_info *ray_info)
{
	ray_info->y_inter = \
		floor((getmap()->player_y)) * (t_double)MINIMAP_SCALE;
	if (ray_info->ray_facing_down)
		ray_info->y_inter += (t_double)MINIMAP_SCALE;
	ray_info->x_inter = \
		getmap()->player_x * MINIMAP_SCALE + ((ray_info->y_inter - getmap()->player_y * MINIMAP_SCALE) \
								/ tan(ray_info->ray_angle));
	ray_info->y_step = (t_double)MINIMAP_SCALE;
	if (ray_info->ray_facing_up)
		ray_info->y_step *= -1;
	ray_info->x_step = (t_double)MINIMAP_SCALE / tan(ray_info->ray_angle);
	if (ray_info->ray_facing_left && ray_info->x_step > 0)
		ray_info->x_step *= -1;
	if (ray_info->ray_facing_right && ray_info->x_step < 0)
		ray_info->x_step *= -1;
	ray_info->next_horizontal_hit_x = ray_info->x_inter;
	ray_info->next_horizontal_hit_y = ray_info->y_inter;
	calculating_horizontal_distances(config, ray_info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:16:31 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:38:11 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	setup(t_global_conf *config)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	config->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "san andreas", false);
	if (!config->mlx)
	{
		printf("[SETUP] Error ==> NO MLX INSTANCE FOUND\n");
		exit(0);
	}
	config->img = mlx_new_image(config->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!config->img || \
		(mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
	{
		printf("[SETUP] Error ==> NO IMAGE FOUND\n");
		exit(0);
	}
	config->player->rotation_angle = 0;
	config->player->color = 0xFF0000FF;
	config->rays = (t_ray *)malloc(sizeof(t_ray) * NUM_OF_RAYS);
	init_ray(config);
	// config->color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * \
	// 	(uint32_t)WINDOW_HEIGHT * (uint32_t)WINDOW_WIDTH);
	/* init_color_buffer(config); */
}

void	init_ray(t_ray_info *ray_info)
{
	ray_info->ray_angle = 0;
	ray_info->wall_hit_x = 0;
	ray_info->wall_hit_y = 0;
	ray_info->distance = 0;
	ray_info->was_hit_vertical = 0;
	ray_info->ray_facing_up = 0;
	ray_info->ray_facing_down = 0;
	ray_info->ray_facing_left = 0;
	ray_info->ray_facing_right = 0;
	ray_info->ray_angle = 0;
	ray_info->next_horizontal_hit_x = 0;
	ray_info->next_horizontal_hit_x = 0;
	ray_info->x_check = 0;
	ray_info->y_check = 0;
	ray_info->next_vertical_hit_x = 0;
	ray_info->next_vertical_hit_y = 0;
	ray_info->horizontal_wall_hit = 0;
	ray_info->horizontal_wall_hit_x = 0;
	ray_info->horizontal_wall_hit_y = 0;
	ray_info->vertical_wall_hit = 0;
	ray_info->vertical_wall_hit_x = 0;
	ray_info->vertical_wall_hit_y = 0;
	ray_info->horizontal_distance = INT_MAX;
	ray_info->vertical_distance = INT_MIN;
}

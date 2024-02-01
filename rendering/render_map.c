/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:42:25 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/01 16:32:44 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_render(t_render *rend)
{
	rend->wall_height = 0;
	rend->distance_to_projection_plane = 0;
	rend->projected_wall_height = 0;
	rend->wall_top = 0;
	rend->wall_ceil = 0;
	rend->correct_distance = 0;
}

void	render_3d(t_global_conf *config, int i)
{
	t_render	renderer;
	int			j;

	init_render(&renderer);
	while (i < NUM_OF_RAYS)
	{
		renderer.correct_distance = config->rays[i].distance * \
			cos(config->rays[i].ray_angle - config->player->rotation_angle);
		renderer.distance_to_projection_plane = \
									(WINDOW_WIDTH / 2) / tan(FOV / 2);
		renderer.projected_wall_height = \
			(MINIMAP_SCALE / renderer.correct_distance) * \
			renderer.distance_to_projection_plane;
		renderer.wall_height = (int)renderer.projected_wall_height;
		renderer.wall_top = (WINDOW_HEIGHT / 2) - (renderer.wall_height / 2);
		if (renderer.wall_top < 0)
			renderer.wall_top = 0;
		renderer.wall_ceil = (WINDOW_HEIGHT / 2) + (renderer.wall_height / 2);
		if (renderer.wall_ceil > WINDOW_HEIGHT)
			renderer.wall_ceil = WINDOW_HEIGHT;
		j = renderer.wall_top;
		while (j < renderer.wall_ceil)
		{
			mlx_put_pixel(config->img, i, j, 0x0000FFFF);
			j++;
		}
		i++;
	}
}

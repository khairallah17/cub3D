/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:42:25 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 22:01:09 by eagoumi          ###   ########.fr       */
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

	init_render(&renderer);
	renderer.distance_to_projection_plane = (WINDOW_WIDTH / 2.0) \
	/ tan(to_rad(FOV) / 2.0);
	renderer.correct_distance = config->rays[i].distance * \
		cos(config->rays[i].ray_angle - getmap()->player_angle);
	renderer.projected_wall_height = (MINIMAP_SCALE / \
	renderer.correct_distance) * renderer.distance_to_projection_plane;
	renderer.wall_height = (int)renderer.projected_wall_height;
	if (renderer.wall_height < 0)
		renderer.wall_height = 0;
	renderer.wall_top = (WINDOW_HEIGHT / 2.0) - (renderer.wall_height / 2.0);
	if (renderer.wall_top < 0)
		renderer.wall_top = 0;
	renderer.wall_ceil = (WINDOW_HEIGHT / 2.0) + (renderer.wall_height / 2.0);
	if (renderer.wall_ceil > WINDOW_HEIGHT)
		renderer.wall_ceil = WINDOW_HEIGHT;
	rendring_texture(config, &renderer, i);
}

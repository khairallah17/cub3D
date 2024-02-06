/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:42:25 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/04 23:56:49 by mkhairal         ###   ########.fr       */
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

//mine
//===============================================================EAGOUMI===============================================================
unsigned int generate_color(t_global_conf *texture, int x, int y, int i)
{
	int	bpp;
	int	width;
	int	height;
	int	offset;

	bpp = texture->rays[i].texture->bytes_per_pixel;
	width = texture->rays[i].texture->width;
	height = texture->rays[i].texture->height;
	if (y < 0)
		y = 0;
	if (y >= height)
		y = height - 1;
	if (x < 0)
		x = 0;
	if (x >= width)
		x = width - 1;
	offset = (y * width + x) * bpp;
	return (pixels_rgba(
		texture->rays[i].texture->pixels[offset + 0],
		texture->rays[i].texture->pixels[offset + 1],
		texture->rays[i].texture->pixels[offset + 2], 255));
}

void  rendring_texture(t_global_conf *tex_cub, t_render *renderer, int j)
{
	tex_cub->i = renderer->wall_ceil;

	int texture_offset_x;
	if (tex_cub->rays[j].was_hit_vertical)
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_y, TILE) * ((float)tex_cub->rays[j].texture->width / TILE);
	else
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_x, TILE) * ((float)tex_cub->rays[j].texture->width / TILE);
	
	tex_cub->i = renderer->wall_top;
	while(tex_cub->i <= renderer->wall_ceil)
	{
		renderer->distance_from_top_floor = tex_cub->i + (renderer->wall_height / 2) - (WINDOW_HEIGHT / 2);
		int texture_offset_y = renderer->distance_from_top_floor * ((float)tex_cub->rays[j].texture->height / renderer->wall_height);
		uint32_t get_color_wall = generate_color(tex_cub, texture_offset_x, texture_offset_y, j);
		cub3d_put_pixel(tex_cub->img, j, tex_cub->i, get_color_wall);
		(tex_cub->i)++;
	}
	tex_cub->i = renderer->wall_ceil;
}

void	render_3d(t_global_conf *config, int i)
{
	t_render	renderer;

	init_render(&renderer);
	renderer.distance_to_projection_plane = (WINDOW_WIDTH / 2.0) / tan(FOV / 2.0);
	renderer.correct_distance = config->rays[i].distance * \
		cos(config->rays[i].ray_angle - getmap()->player_angle);
	renderer.projected_wall_height = (MINIMAP_SCALE / renderer.correct_distance) * renderer.distance_to_projection_plane;
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

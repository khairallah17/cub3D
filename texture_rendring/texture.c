/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:42:45 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 20:50:27 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	generate_color(t_global_conf *texture, int x, int y, int i)
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
	return (pixels_rgba(texture->rays[i].texture->pixels[offset + 0],
			texture->rays[i].texture->pixels[offset + 1],
			texture->rays[i].texture->pixels[offset + 2], 255));
}

void	rendring_texture(t_global_conf *tex_cub, t_render *renderer, int j)
{
	int			texture_offset_x;
	int			texture_offset_y;
	uint32_t	get_color_wall;

	tex_cub->i = renderer->wall_ceil;
	if (tex_cub->rays[j].was_hit_vertical)
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_y, TILE) \
	* ((float)tex_cub->rays[j].texture->width / TILE);
	else
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_x, TILE) \
	* ((float)tex_cub->rays[j].texture->width / TILE);
	tex_cub->i = renderer->wall_top;
	while (tex_cub->i <= renderer->wall_ceil)
	{
		renderer->distance_from_top_floor = tex_cub->i + \
		(renderer->wall_height / 2) - (WINDOW_HEIGHT / 2);
		texture_offset_y = renderer->distance_from_top_floor * \
		((float)tex_cub->rays[j].texture->height / renderer->wall_height);
		get_color_wall = generate_color(tex_cub, \
		texture_offset_x, texture_offset_y, j);
		cub3d_put_pixel(tex_cub->img, j, tex_cub->i, get_color_wall);
		(tex_cub->i)++;
	}
	tex_cub->i = renderer->wall_ceil;
}

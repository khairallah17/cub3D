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
unsigned int generate_color(t_global_conf *texture, int y, int x, int i)
{
	int r;
	int g;
	int b;
	int get_color_pixel;

	get_color_pixel = (y * (texture->rays[i].texture->width * 4)) + (x * 4);
	// printf("get_color_pixel = %d\n", get_color_pixel);
	// printf("y = %d\n", x);
	// printf("x = %d\n", texture->rays[i].texture->width);
	// exit(1);
	r = texture->rays[i].texture->pixels[get_color_pixel];
	// printf("r = %d\n", r);
	g = texture->rays[i].texture->pixels[get_color_pixel + 1];
	b = texture->rays[i].texture->pixels[get_color_pixel + 2];
	return (pixels_rgba(r, g, b, 255));
}

void  rendring_texture(t_global_conf *tex_cub, t_render *renderer, int j)
{

	// t_ray_info	angle_nomalize;
	unsigned int store_color_floor;
	unsigned int store_color_ceiling;
	// angle_nomalize.ray_angle = correct_angle(angle_nomalize.ray_angle);

    store_color_floor = tex_cub->cub->prs_map.f_c_color.floor;
    store_color_ceiling = tex_cub->cub->prs_map.f_c_color.ceiling;
	// coloring_floor_ceilling(tex_cub, );
	//rendring Ceilling
	tex_cub->i = renderer->wall_ceil;
	// printf("floor color == %d\n", store_color_floor);
	// while (tex_cub->i < WINDOW_HEIGHT)
	// 	mlx_put_pixel(tex_cub->img, j, (tex_cub->i)++, store_color_floor);
	// printf("floor color == %d\n", store_color_floor);
	//rendring Floor
	tex_cub->i = 0;
	// while (tex_cub->i < renderer->wall_ceil)
	// 	mlx_put_pixel(tex_cub->img, j, (tex_cub->i)++, store_color_ceiling);
	int texture_offset_x;
	// printf("pppppppopopopopopopopopopopopopopopopopopowidth %d\n", j);
	if (tex_cub->rays[j].was_hit_vertical)
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_y, TILE) * ((float)tex_cub->rays[j].texture->width / TILE);
		// texture_offset_x = fmodf(tex_cub->rays->wall_hit_y * tex_cub->rays[j].texture->width / TILE, tex_cub->rays[j].texture.width);
	else
		texture_offset_x = fmodf(tex_cub->rays[j].wall_hit_x, TILE) * ((float)tex_cub->rays[j].texture->width / TILE);
		// texture_offset_x = (int)fmodf(tex_cub->rays->wall_hit_y * (tex_cub->rays[j].texture->width / TILE), tex_cub->rays[j].texture.width);
	// printf("renderer->distance_to_projection_plane = %d\n", renderer->distance_to_projection_plane);
	// printf("offset_x = %d\n", texture_offset_x);
	// exit(1);
	// exit(1);
	
	tex_cub->i = renderer->wall_top;
	while(tex_cub->i < renderer->wall_ceil)
	{
		renderer->distance_from_top_floor = tex_cub->i + (renderer->wall_height / 2) - (WINDOW_HEIGHT / 2);
		// printf("height = %d\n", tex_cub->i + (renderer->wall_height / 2));
		int texture_offset_y = renderer->distance_from_top_floor * ((float)tex_cub->rays[j].texture->height / renderer->wall_height);
		// printf("offset_y = %f\n", texture_offset_y);
		// exit(1);
		uint32_t get_color_wall = generate_color(tex_cub, texture_offset_x, texture_offset_y, j);
		// printf("get_color_wall = %d\n", get_color_wall);
		// printf("o = %d\n", tex_cub->i);
		
		mlx_put_pixel(tex_cub->img, j, tex_cub->i, get_color_wall);
		(tex_cub->i)++;
	}
	tex_cub->i = renderer->wall_ceil;
}
//===============================================================EAGOUMI===============================================================
//mine

void	render_3d(t_global_conf *config, int i)
{
	t_render	renderer;
	int			j;

	// config->j = 0;
	init_render(&renderer);
	renderer.distance_to_projection_plane = \
								(WINDOW_WIDTH / 2) / tan(FOV / 2);
	renderer.correct_distance = config->rays[i].distance * \
		cos(config->rays[i].ray_angle - config->player->rotation_angle);
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
	rendring_texture(config, &renderer, i);
	// j = renderer.wall_top;
	// while (j < renderer.wall_ceil)
	// {
	// 	mlx_put_pixel(config->img, i, j, 0x0000FFFF);
	// 	j++;
	// }
}

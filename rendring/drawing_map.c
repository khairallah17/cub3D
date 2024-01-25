/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:19:18 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 16:19:58 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int main ()
{
	t_global_conf   conf;
	t_player        player;
	mlx_t           *mlx;
	mlx_image_t     *img;

	img = NULL;
	mlx = NULL;
	conf.img = img;
	conf.mlx = mlx;
	conf.player = &player;
	setup(&conf);
	int i = 0;
	while (i < MAP_NUM_ROWS) {
		int j = 0;
		while (j < MAP_NUM_COLS) {
			if (map[i][j] == '1')
				draw(&conf, j, i, 0xFFFFFF);
			else if (map[i][j] == '0')
				draw(&conf, j, i, 0x000000);
			else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S') {
				conf.player->x = j;
				conf.player->y = i;
				draw(&conf, j, i, 0x000000);
			}
			j++;
		}
		i++;
	}
	draw_player(&conf);
	render_3d(&conf);
	render_color_buffer(&conf);

	// free(conf.rays);

	mlx_key_hook(conf.mlx, key_hook, &conf);
	mlx_loop(conf.mlx);
	mlx_close_hook(conf.mlx, close_key_hook, &conf);
}
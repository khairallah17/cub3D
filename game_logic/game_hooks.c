/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:53:35 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/05 00:09:30 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	update(t_global_conf *conf)
{
	mlx_delete_image(conf->mlx, conf->img);

	conf->img = mlx_new_image(conf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// render_3d(conf);
	// draw_map(conf);
	// draw_player(conf);
	cast_all_rays(conf);

	mlx_image_to_window(conf->mlx ,conf->img , 0, 0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_global_conf	*conf;

	conf = param;
	printf("UPDATING\n");
	player_movements_checker(conf, &keydata);
}

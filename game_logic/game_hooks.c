/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:53:35 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:21 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	close_key_hook(void *param)
{
	t_global_conf	*conf;

	conf = param;
	mlx_delete_image(conf->mlx, conf->img);
	mlx_close_window(conf->mlx);
	free(conf->rays);
	free(conf->color_buffer);
}

void	update(t_global_conf *conf)
{
	int	i;
	int	j;

	i = 0;
	mlx_delete_image(conf->mlx, conf->img);
	conf->img = mlx_new_image(conf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(conf->mlx ,conf->img , 0, 0);
	render_3d(conf);
	render_color_buffer(conf);
	draw_map(conf);
}

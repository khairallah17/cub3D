/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:53:35 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/06 23:05:46 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	update(t_global_conf *conf)
{
	cub3d_clear_image(conf->img);
	cast_all_rays(conf);
	mlx_image_to_window(conf->mlx, conf->img, 0, 0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
		player_movements_checker((t_global_conf *)param, &keydata);
}

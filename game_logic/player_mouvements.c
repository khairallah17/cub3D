/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:25:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/05 00:11:56 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_player(t_double angle)
{
	t_double	x;
	t_double	y;
	t_double	v;
	t_double	d;

	d = 0.0;
	v = 0.1;
	if (v >= getmap()->player_speed)
		v = getmap()->player_speed / 2.0;
	while (d < getmap()->player_speed)
	{
		x = getmap()->player_x + v * cos(getmap()->player_angle + angle);
		y = getmap()->player_y + v * sin(getmap()->player_angle + angle);
		if (wall_collision(NULL, x, y))
			break ;
		getmap()->player_x = x;
		getmap()->player_y = y;
		d += v;
	}
}

void	player_movements_checker(t_global_conf *config, mlx_key_data_t *key)
{
	if (key->key == MLX_KEY_ESCAPE)
		cub3d_exit(config);
	if (key->key == MLX_KEY_LEFT)
		getmap()->player_angle -= getmap()->player_rotation_angle;
	else if (key->key == MLX_KEY_RIGHT)
		getmap()->player_angle += getmap()->player_rotation_angle;
	if (key->key == MLX_KEY_W)
		move_player(0.0);
	else if (key->key == MLX_KEY_S)
		move_player(M_PI);
	else if (key->key == MLX_KEY_A)
		move_player(-M_PI_2);
	else if (key->key == MLX_KEY_D)
		move_player(M_PI_2);
	update(config);
}

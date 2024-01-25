/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:25:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:15:10 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_movements_checker(t_global_conf *config, mlx_key_data *key)
{
	if (keydata.key == MLX_KEY_LEFT)
		conf->player->rotation_angle -= 0.1;
	else if (keydata.key == MLX_KEY_RIGHT)
		conf->player->rotation_angle += 0.1;
	else if (keydata.key == MLX_KEY_W && conf->player->x > 0)
		move_up(config);
	else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS)
		move_down(config);
	else if (keydata.key == MLX_KEY_A && conf->player->y > 0)
		move_left(config);
	else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS)
		move_right(config);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_delete_image(conf->mlx, conf->img);
		mlx_close_window(conf->mlx);
		free(conf->rays);
		free(conf->color_buffer);
		return ;
	}
	update(config);
}

void	move_up(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x + (0.1 * cos(config->player->rotation_angle));
	y = config->player->y + (0.1 * sin(config->player->rotation_angle));
	if (!wall_collision(x, y))
	{
		config->player->x += 0.1 (cos(config->player->rotation_angle));
		config->player->y += 0.1 (cos(config->player->rotation_angle));
	}
}

void	move_down(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x - (0.1 * cos(config->player->rotation_angle));
	y = config->player->y - (0.1 * sin(config->player->rotation_angle));
	if (!wall_collision(x, y))
	{
		config->player->x -= 0.1 (cos(config->player->rotation_angle));
		config->player->y -= 0.1 (cos(config->player->rotation_angle));
	}
}

void	move_left(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x + (0.05 * cos(config->player->rotation_angle));
	y = config->player->y + (0.05 * sin(config->player->rotation_angle));
	if (!wall_collision(x, y))
	{
		config->player->x += 0.05 (cos(config->player->rotation_angle));
		config->player->y += 0.05 (cos(config->player->rotation_angle));
	}
}

void	move_right(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x - (0.05 * cos(config->player->rotation_angle));
	y = config->player->y - (0.05 * sin(config->player->rotation_angle));
	if (!wall_collision(x, y))
	{
		config->player->x -= 0.05 (cos(config->player->rotation_angle));
		config->player->y -= 0.05 (cos(config->player->rotation_angle));
	}
}

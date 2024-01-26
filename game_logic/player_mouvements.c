/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:25:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/26 15:50:36 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_movements_checker(t_global_conf *config, mlx_key_data_t *key)
{
	if (key->key == MLX_KEY_LEFT)
		config->player->rotation_angle -= 0.1;
	else if (key->key == MLX_KEY_RIGHT)
		config->player->rotation_angle += 0.1;
	else if (key->key == MLX_KEY_W && config->player->x > 0)
		move_up(config);
	else if (key->key == MLX_KEY_S && config->player->x < MAP_NUM_ROWS)
		move_down(config);
	else if (key->key == MLX_KEY_A && config->player->y > 0)
		move_left(config);
	else if (key->key == MLX_KEY_D && config->player->y < MAP_NUM_COLS)
		move_right(config);
	else if (key->key == MLX_KEY_ESCAPE)
	{
		mlx_delete_image(config->mlx, config->img);
		mlx_close_window(config->mlx);
		free(config->rays);
		free(config->color_buffer);
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
	if (!wall_collision(config, x, y))
	{
		config->player->x += (0.1 * cos(config->player->rotation_angle));
		config->player->y += (0.1 * sin(config->player->rotation_angle));
	}
}

void	move_down(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x - (0.1 * cos(config->player->rotation_angle));
	y = config->player->y - (0.1 * sin(config->player->rotation_angle));
	if (!wall_collision(config, x, y))
	{
		config->player->y -= (0.1 * cos(config->player->rotation_angle));
		config->player->x -= (0.1 * sin(config->player->rotation_angle));
	}
}

void	move_left(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x + (0.05 * cos(config->player->rotation_angle));
	y = config->player->y + (0.05 * sin(config->player->rotation_angle));
	if (!wall_collision(config, x, y))
	{
		config->player->x += (0.05 * cos(config->player->rotation_angle));
		config->player->y += (0.05 * sin(config->player->rotation_angle));
	}
}

void	move_right(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x - (0.05 * cos(config->player->rotation_angle));
	y = config->player->y - (0.05 * sin(config->player->rotation_angle));
	if (!wall_collision(config, x, y))
	{
		config->player->x -= (0.05 * cos(config->player->rotation_angle));
		config->player->y -= (0.05 * sin(config->player->rotation_angle));
	}
}

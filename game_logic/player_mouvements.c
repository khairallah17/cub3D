/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:25:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/31 16:36:32 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_movements_checker(t_global_conf *config, mlx_key_data_t *key)
{
	if (key->key == MLX_KEY_LEFT && (key->action == MLX_PRESS || key->action == MLX_REPEAT))
		config->player->rotation_angle -= 0.2;
	else if (key->key == MLX_KEY_RIGHT && (key->action == MLX_PRESS || key->action == MLX_REPEAT))
		config->player->rotation_angle += 0.2;
	else if (key->key == MLX_KEY_W && config->player->x > 0)
		move_up(config);
	else if (key->key == MLX_KEY_S && config->player->x < config->cub->prs_map.map.width)
		move_down(config);
	else if (key->key == MLX_KEY_A && config->player->y > 0)
		move_left(config);
	else if (key->key == MLX_KEY_D && config->player->y < config->cub->prs_map.map.height)
		move_right(config);
	else if (key->key == MLX_KEY_ESCAPE)
	{
		mlx_delete_image(config->mlx, config->img);
		mlx_close_window(config->mlx);
		free(config->rays);
		// free(config->color_buffer);
		exit(0);
	}
}

void	move_up(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x + (0.2 * cos(config->player->rotation_angle));
	y = config->player->y + (0.2 * sin(config->player->rotation_angle));
	if (!wall_collision(config, x, y))
	{
		config->player->x += (0.2 * cos(config->player->rotation_angle));
		config->player->y += (0.2 * sin(config->player->rotation_angle));
	}
}

void	move_down(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x - (0.2 * cos(config->player->rotation_angle));
	y = config->player->y - (0.2 * sin(config->player->rotation_angle));
	if (!wall_collision(config, x, y))
	{
		config->player->x -= (0.2 * cos(config->player->rotation_angle));
		config->player->y -= (0.2 * sin(config->player->rotation_angle));
	}
}

void	move_left(t_global_conf *config)
{
	int		x;
	int		y;
	double	px;
	double	py;
	double	ra;

	px = config->player->x;
	py = config->player->y;
	ra = config->player->rotation_angle;
	x = px - (0.25 * cos(config->player->rotation_angle + M_PI / 2));
	y = py - (0.25 * sin(config->player->rotation_angle + M_PI / 2));
	if (!wall_collision(config, x, y))
	{
		config->player->x -= (0.25 * cos(ra + M_PI / 2));
		config->player->y -= (0.25 * sin(ra + M_PI / 2));
	}
}

void	move_right(t_global_conf *config)
{
	int	x;
	int	y;

	x = config->player->x + (0.25 * cos(config->player->rotation_angle \
		+ M_PI / 2));
	y = config->player->y + (0.25 * sin(config->player->rotation_angle \
		+ M_PI / 2));
	if (!wall_collision(config, x, y))
	{
		config->player->x += (0.25 * cos(config->player->rotation_angle \
			+ M_PI / 2));
		config->player->y += (0.25 * sin(config->player->rotation_angle \
			+ M_PI / 2));
	}
}

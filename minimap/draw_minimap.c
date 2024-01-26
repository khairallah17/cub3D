/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:54:46 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/26 18:44:26 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw(t_global_conf *config, int x, int y, uint32_t color)
{
	int	i;
	int	tile;
	int	j;

	if (!config->img)
	{
		printf("[DRAW] Error ==> NO IMAGE\n");
		exit(0);
	}
	else if (!config->mlx)
	{
		printf("[DRAW] Error ==> NO MLX\n");
		exit(0);
	}
	i = 0;
	tile = MINIMAP_SCALE;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			mlx_put_pixel(config->img, (MINIMAP_SCALE * x) + i, \
			(MINIMAP_SCALE * y) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_global_conf *config)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < config->cub->prs_map.map.width)
	{
		j = 0;
		while (j < config->cub->prs_map.map.height)
		{
			if (config->cub->prs_map.map.map_grid[j][i] == '1')
				draw(config, j, i, 0x00FFFFFF);
			else
				draw(config, j, i, 0x000000FF);
			j++;
		}
		i++;
	}
	draw_player(config);
}

void	draw_player(t_global_conf *config)
{
	int	i;
	int	j;
	int	tile;

	i = 0;
	tile = PLAYER_TILE / 2;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x) + i, \
				(MINIMAP_SCALE * config->player->y) + j, config->player->color);
			// mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x) - i, \
			// 	(MINIMAP_SCALE * config->player->y) - j, config->player->color);
			// mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x) + i, \
			// 	(MINIMAP_SCALE * config->player->y) - j, config->player->color);
			// mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x) - i, \
			// 	(MINIMAP_SCALE * config->player->y) + j, config->player->color);
			j++;
		}
		i++;
	}
    // draw_single_line(config);
	cast_all_rays(config);
}

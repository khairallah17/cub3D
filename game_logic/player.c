/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:33:42 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/05 00:13:24 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_init(t_global_conf *config)
{
	get_player(config);
	config->player->rotation_angle = 0;
	config->player->rotation_speed = 0;
	config->player->speed = 0;
	config->player->direction = 0;
	config->player->color = 0xFFFF00FF;
}

void	get_player(t_global_conf *config)
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
			if (config->cub->prs_map.map.map_grid[i][j])
			{
				config->player->x = j + MINIMAP_SCALE / 2;
				config->player->y = i;
				return ;
			}
		}
		i++;
	}
}

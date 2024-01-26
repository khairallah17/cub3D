/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/26 15:50:52 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	wall_collision(t_global_conf *config, double x, double y)
{
	int	minimap_height;
	int	minimap_width;

	minimap_height = config->cub->prs_map.map.height * MINIMAP_SCALE;
	minimap_width = config->cub->prs_map.map.width * MINIMAP_SCALE;
	if (x < 0 || (int)x >= minimap_width || y < 0 || (int)y >= minimap_height)
		return (0);
	return (config->cub->prs_map.map.map_grid[(int)(y)][(int)(x)] == '1');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/06 21:51:52 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	wall_collision(t_global_conf *config, float x, float y)
{
	int	px;
	int	py;

	px = getmap()->player_x;
	py = getmap()->player_y;
	if ((map_get10(px, (int)(y)) == '1' \
		&& map_get10((int)(x), py) == '1'))
		return (1);
	return ((map_get10(x, y) == '1') || (map_get10(x, y) == ' '));
}

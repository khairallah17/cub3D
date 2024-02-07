/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 19:25:08 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	wall_collision2(float x, float y)
{
	int	px;
	int	py;

	px = getmap()->player_x;
	py = getmap()->player_y;
	return (((map_get10(x, y) == '1') || (map_get10(x, y) == ' ')) || \
	((map_get10(px, y) == '1') && (map_get10(x, py) == '1')));
}

int	wall_collision(float x, float y)
{
	return (((map_get10(x, y) == '1') || (map_get10(x, y) == ' ')));
}

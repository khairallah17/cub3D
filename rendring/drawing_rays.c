/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:18:40 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:23:07 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_rays(t_global_conf *config, int pos)
{
	t_line_coordinates	line;
	double				tmp;

	line.px = floor(config->player->x * MINIMAP_SCALE);
	line.py = floor(config->player->y * MINIMAP_SCALE);
	line.dx = floor(config->rays[pos].wall_hit_x);
	line.dy = floor(config->rays[pos].wall_hit_y);
	line.slope = (line.py - line.dy) / (line.px - line.dx);
	line.y_intercept = line.py - line.slope * line.px;
	if (line.px >= line.dx)
	{
		tmp = line.px;
		line.px = line.dx;
		line.dx = tmp;
	}
	while (line.px <= line.dx)
	{
		mlx_put_pixel(config->img, line.px, \
			line.slope * line.px + line.y_intercept, 0x008000FF);
		line.px += 0.01;
	}
}
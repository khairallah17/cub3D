/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:52:01 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/07 18:34:21 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	pixels_rgba(int r, int g, int b, int a)
{
	return ((unsigned int)r << 24 | (unsigned int)g << 16 \
	| (unsigned int)b << 8 | (unsigned int)a);
}

int	cub3d_exit(t_global_conf *config)
{
	if (config)
	{
		mlx_delete_image(config->mlx, config->img);
		mlx_close_window(config->mlx);
	}
	exit(0);
	return (0);
}

void	cub3d_put_pixel(
	mlx_image_t *img,
	uint32_t x,
	uint32_t y,
	uint32_t color)
{
	if (y < 0)
		y = 0;
	if (y >= WINDOW_HEIGHT)
		y = WINDOW_HEIGHT - 1;
	if (x < 0)
		x = 0;
	if (x >= WINDOW_WIDTH)
		x = WINDOW_WIDTH - 1;
	mlx_put_pixel(img, x, y, color);
}

void	cub3d_clear_image(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < (int)img->width)
	{
		y = 0;
		while (y < (int)img->height)
		{
			if (y < (int)(img->height / 2))
				cub3d_put_pixel(img, x, y, getmap()->ceiling);
			else
				cub3d_put_pixel(img, x, y, getmap()->floor);
			y++;
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	launch(ac, av);
}

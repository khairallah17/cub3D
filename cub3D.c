/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:52:01 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/26 15:34:44 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static t_cub3d	*cub;

// void	ft_free(t_cub3d *cub)
// {
// 	int	i;

// 	i = 0;
// 	while (cub->prs_map.map.map_grid[i])
// 		free(cub->prs_map.map.map_grid[i++]);
// 	free(cub->prs_map.map.map_grid);
// 	free(cub->path_maps);
// 	if (cub->prs_map.texture.east != NULL)
// 		free(cub->prs_map.texture.east);
// 	if (cub->prs_map.texture.north != NULL)
// 		free(cub->prs_map.texture.north);
// 	if (cub->prs_map.texture.south != NULL)
// 		free(cub->prs_map.texture.south);
// 	if (cub->prs_map.texture.west != NULL)
// 		free(cub->prs_map.texture.west);
// 	free(cub);
// }

// void	inf(void)
// {
// 	system("leaks cub3D");
// }

// void    draw(void *parp)
// {
//     int        i;

//     i = 0;
// 	cub = (t_cub3d *)parp;
//     while (i < cub->prs_map.map.height)
//     {
//         int j = 0;
//         while (j < cub->prs_map.map.width)
//         {
// 			puts("s");
//             if (cub->prs_map.map.map_grid[i][j] == '1')
//                 mlx_put_pixel(cub->mlx.window, i, j, 0x0FAFFF);
//             else if (cub->prs_map.map.map_grid[i][j] == '0')
//                 mlx_put_pixel(cub->mlx.window, i, j, 0x000000);
// 			else if (cub->prs_map.map.map_grid[i][j] == 'N')
//                 mlx_put_pixel(cub->mlx.window, i, j, 0xEEEEEE);
//             j=j*32;
//         }
// 		// printf("%s", cub->prs_map.map.map_grid[i]);
// 		i=i*32;
//     }
// }

// int	main(int ac, char **av)
// {

// 	atexit(inf);
// 	cub = parsing(ac, av);
// 	printf("%p\n", cub);
// 	//check map
// 	check_map(cub);
// 	int i = 0;
//     while (i < cub->prs_map.map.height)
//     {
// 		printf("%s\n", cub->prs_map.map.map_grid[i++]);
// 	}	
// 	//mlx window
// 	if (!(cub->mlx.mlx = mlx_init(cub->prs_map.map.height, cub->prs_map.map.width, "cub3D", true)))
// 	{
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(cub->mlx.window = mlx_new_image(cub->mlx.mlx, cub->prs_map.map.height, cub->prs_map.map.width)))
// 	{
// 		mlx_close_window(cub->mlx.mlx);
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(cub->mlx.mlx, cub->mlx.window, 0, 0) == -1)
// 	{
// 		mlx_close_window(cub->mlx.mlx);
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	// t_cub3d *cubb;
// 	mlx_loop_hook(cub->mlx.mlx, draw, cub);
// 	mlx_loop(cub->mlx.mlx);
// 	mlx_terminate(cub->mlx.mlx);
// 	ft_free(cub);
// }


int	main(int ac, char **av)
{
	launch(ac, av);
}

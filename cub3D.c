#include "cub3D.h"

int main(int ac, char **av)
{
    t_cub3d *cub;

    cub = parsing(ac, av);
    //check map
    cub->mlx.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
    if (!(cub->mlx.window = mlx_new_image(cub->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(cub->mlx.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (mlx_image_to_window(cub->mlx.mlx, cub->mlx.window, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    mlx_loop(cub->mlx.mlx);
	mlx_terminate(cub->mlx.mlx);
    // while(1);
}
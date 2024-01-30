// #include "../cub3d.h"

// void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
// {
// 	int		i;
// 	int		c;

// 	i = b_pix;
// 	c = get_rgba(ft_atoi(mlx->dt->ff[0]), ft_atoi(mlx->dt->ff[1]), \
// 		ft_atoi(mlx->dt->ff[2]), 255);
// 	while (i < S_H)//heigh_window
// 		my_mlx_pixel_put(mlx, ray, i++, c);
// 	c = get_rgba(ft_atoi(mlx->dt->cc[0]), ft_atoi(mlx->dt->cc[1]), \
// 		ft_atoi(mlx->dt->cc[2]), 255);
// 	i = 0;
// 	while (i < t_pix)
// 		my_mlx_pixel_put(mlx, ray, i++, c);
// }

// mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
// {
// 	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
// 	if (flag == 0)
// 	{
// 		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
// 			return (mlx->tex->ea);
// 		else
// 			return (mlx->tex->we);
// 	}
// 	else
// 	{
// 		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
// 			return (mlx->tex->so);
// 		else
// 			return (mlx->tex->no);
// 	}
// }

// double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
// {
// 	double	x_o;

// 	if (mlx->ray->flag == 1)
// 		x_o = (int)fmodf((mlx->ray->horiz_x * \
// 		(texture->width / TILE_SIZE)), texture->width);
// 	else
// 		x_o = (int)fmodf((mlx->ray->vert_y * \
// 		(texture->width / TILE_SIZE)), texture->width);
// 	return (x_o);
// }

// void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
// {
// 	double			x_o;
// 	double			y_o;
// 	mlx_texture_t	*texture;
// 	uint32_t		*arr;
// 	double			factor;

// 	texture = get_texture(mlx, mlx->ray->flag);
// 	arr = (uint32_t *)texture->pixels;
// 	factor = (double)texture->height / wall_h;
// 	x_o = get_x_o(texture, mlx);
// 	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (t_pix < b_pix)
// 	{
// 		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes \
// 		(arr[(int)y_o * texture->width + (int)x_o]));
// 		y_o += factor;
// 		t_pix++;
// 	}
// }

// void	render_wall(t_mlx *mlx, int ray)
// {
// 	double	wall_h;
// 	double	b_pix;
// 	double	t_pix;

// 	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
// 	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / \
// 	tan(mlx->ply->fov_rd / 2));
// 	b_pix = (S_H / 2) + (wall_h / 2);
// 	t_pix = (S_H / 2) - (wall_h / 2);
// 	if (b_pix > S_H)
// 		b_pix = S_H;
// 	if (t_pix < 0)
// 		t_pix = 0;
// 	mlx->ray->index = ray;
// 	draw_wall(mlx, t_pix, b_pix, wall_h);
// 	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
// }

// int	get_rgba(int r, int g, int b, int a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a << 0);
// }

// int	reverse_bytes(int c)
// {
// 	unsigned int	b;

// 	b = 0;
// 	b |= (c & 0xFF) << 24;
// 	b |= (c & 0xFF00) << 8;
// 	b |= (c & 0xFF0000) >> 8;
// 	b |= (c & 0xFF000000) >> 24;
// 	return (b);
// }

// void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
// {
// 	if (x < 0)
// 		return ;
// 	else if (x >= S_W)
// 		return ;
// 	if (y < 0)
// 		return ;
// 	else if (y >= S_H)
// 		return ;
// 	mlx_put_pixel(mlx->img, x, y, color);
// }

// float	nor_angle(float angle)
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }

// int	unit_circle(float angle, char c)
// {
// 	if (c == 'x')
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (1);
// 	}
// 	else if (c == 'y')
// 	{
// 		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
// 			return (1);
// 	}
// 	return (0);
// }

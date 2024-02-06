t_map3d	*getmap(void)
{
	static t_map3d	map;

	return (&map);
}

int	ft_extcmp(const char *file, const char *ext)
{
	int	p;
	int	i;
	int	k;

	p = 0;
	i = 0;
	k = 0;
	while (ext && ext[k])
		k++;
	while (file && file[i])
	{
		if (file[i] == '/')
			p = i + 1;
		i++;
	}
	if ((k < 2) || (i - p < 3) || (i - p <= k)
		|| (file[p] == '.') || (ft_strncmp(file + i - k, ext, k) != 0))
		return (0);
	return (1);
}

void	map_error(const char *msgerr)
{
	close(getmap()->fd);
	free(getmap()->map1d);
	write(2, msgerr, ft_strlen(msgerr));
	write(2, "\n", 1);
	exit (EXIT_FAILURE);
}

char	map_get10(int x, int y)
{
	t_map3d	*map;

	map = getmap();
	if ((x < 0) || (y < 0) || (x >= map->width) || (y >= map->height))
		return (' ');
	return (map->map1d[y * map->width + x]);
}

int	is_surrounded_by_spaces(int x, int y)
{
	if (ft_strchr("NEWS0", map_get10(x, y)))
	{
		if (map_get10(x - 1, y + 0) == ' ')
			map_error("invalid map!");
		if (map_get10(x + 1, y + 0) == ' ')
			map_error("invalid map!");
		if (map_get10(x - 0, y + 1) == ' ')
			map_error("invalid map!");
		if (map_get10(x - 0, y - 1) == ' ')
			map_error("invalid map!");
	}
}

void	map_check(t_map3d *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			is_surrounded_by_spaces(x, y);
			if (ft_strchr("NEWS", map_get10(x, y)))
			{
				getmap()->player_x = x + 0.5;
				getmap()->player_y = y + 0.5;
				if (map_get10(x, y) == 'N')
					map->player_angle = M_PI * 1.5;
				if (map_get10(x, y) == 'W')
					map->player_angle = M_PI * 1.0;
				if (map_get10(x, y) == 'S')
					map->player_angle = M_PI * 0.5;
			}
		}
	}
}

void	open_cubfile(char *cubfile)
{
	if (ft_extcmp(cubfile, ".cub") == 0)
		map_error("Error: In Map Reading it should be <MAP_NAME.CUB>");
	getmap()->filename = cubfile;
	getmap()->fd = open(cubfile, O_RDONLY);
	if (getmap()->fd < 0)
		map_error("Error: can't open file!");
}

int	ft_copypath(t_map3d *map, char *dst, char *c)
{
	int	p;
	int	last_space_pos;

	if ((ft_mapreadch(map, c) != 1) || (!ft_isstab(*c) || (*dst != '\0')))
		return (-1);
	p = 0;
	last_space_pos = -1;
	ft_skipcharset(map, c, " \t");
	while ((*c != '\r') && (*c != '\n') && (*c != '\0') && (p < PATH_MAX))
	{
		dst[p] = *c;
		if ((p > 0) && (!ft_strchr(" \t", dst[p - 1]))
			&& (ft_strchr(" \t\r\v\f\n", dst[p])))
			last_space_pos = p;
		ft_mapreadch(map, c);
		p++;
	}
	if ((p < 1) || (p >= PATH_MAX))
		return (-1);
	if ((last_space_pos != -1) && (ft_strchr(" \t", dst[p - 1])))
		dst[last_space_pos] = 0;
	map->flags_number++;
	if (ft_extcmp(dst, ".png") == 0)
		map_error("Error: invalid png path!");
	return (0);
}

ssize_t	ft_mapreadch(t_map3d *map, char *c)
{
	ssize_t	ret;

	ret = read(getmap()->fd, c, 1);
	if (ft_isline(*c))
	{
		map->lines++;
	}
	if (ret < 1)
		*c = 0;
	map->offset++;
	return (ret);
}

char	ft_skipcharset(t_map3d *map, char *c, const char *charset)
{
	while (*c && ft_strchr(charset, *c))
	{
		if (ft_mapreadch(map, c) != 1)
		{
			*c = 0;
			return (*c);
		}
	}
	return (*c);
}

int	ft_atobyte(int n, char *c)
{
	int	p;
	int	byte;

	p = 0;
	byte = 0;
	while ((p < 3) && ('0' <= *c) && (*c <= '9'))
	{
		if ((byte == 0) && (p == 1))
			map_error("Error: invalid color!");
		byte = 10 * byte + (*c - '0');
		if (ft_mapreadch(map, c) != 1)
			map_error("Error: can't read next character!");
		p++;
	}
	if ((p < 1) || (byte > 255) || ((n < 2) && (*c != ','))
		|| ((n == 2) && !ft_isline(*c)))
		map_error("Error: invalid color!");
	return (byte);
}

int	ft_copycolor(t_map3d *map, unsigned int *bgr, char *c)
{
	int	p;
	int	byte;
	int	n;

	if ((ft_mapreadch(map, c) != 1) || (!ft_isstab(*c) || (*bgr != 0)))
		return (-1);
	*bgr = 0x000000FF;
	n = 0;
	while (n < 3)
	{
		ft_skipcharset(map, c, " \t");
		byte = ft_atobyte(c);
		ft_skipcharset(map, c, " \t");
		*bgr |= (byte << 8 * (3 - n));
		if (!ft_isline(*c) && (ft_mapreadch(map, c) != 1))
			return (-1);
		n++;
	}
	map->flags_number++;
	return (0);
}

void	fill_map_body(t_map3d *map)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (1)
	{
		x = 0;
		c = 1;
		while (1)
		{
			ft_mapreadch(map, &c);
			if ((c == '\0') || (c == '\n'))
				break ;
			map->map1d[y * map->width + x++] = c;
		}
		while (x < map->width)
			map->map1d[y * map->width + x++] = ' ';
		if (c == '\0')
			break ;
		y++;
	}
}

void	read_map_body(t_map3d *map)
{
	char	c;
	int		i;

	map->map1d = malloc(map->width * map->height + 1);
	if (!map->map1d)
		map_error("can't allocate memory!");
	map->map1d[map->width * map->height] = 0;
	close(getmap()->fd);
	getmap()->fd = open(map->filename, O_RDONLY);
	i = 0;
	while ((i < map->bodystart) && (read(getmap()->fd, &c, 1) == 1))
		i++;
	fill_map_body(map);
	map_check(map);
	close(getmap()->fd);
}

void	update_map_width(int *first_index, int *last_index)
{
	int	len;

	len = *last_index - *first_index;
	if (((map->width > 0) && (len < 1)) || (map->players > 1))
		map_error("invalid map!");
	if (map->width < len)
		map->width = len;
	*first_index = map->offset;
	*last_index = map->offset;
	if (map->width == 0)
		map->bodystart = map->offset;
	if (map->width)
		map->height++;
}

void	getmapsize(t_map3d *map)
{
	char	c;
	int		first_index;
	int		last_index;

	first_index = map->offset;
	last_index = map->offset;
	map->bodystart = map->offset;
	c = 1;
	map->players = 0;
	while (c != '\0')
	{
		ft_mapreadch(map, &c);
		if (!ft_strchr("01 NSEW\n", c))
			map_error("invalid map character!");
		map->players += ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'));
		if (c && !ft_isspace(c))
			last_index = map->offset;
		if ((c == '\n') || (c == '\0'))
			update_map_width(&first_index, &last_index);
	}
}

void	map_load_files(t_map3d	*map)
{
	if (((c == 'N') && ((ft_mapreadch(map, &c) != 1) || (c != 'O')
				|| (ft_copypath(map, map->north, &c) == -1)))
		|| ((c == 'E') && ((ft_mapreadch(map, &c) != 1)
				|| (c != 'A') || (ft_copypath(map, map->east, &c) == -1)))
		|| ((c == 'W') && ((ft_mapreadch(map, &c) != 1) || (c != 'E')
				|| (ft_copypath(map, map->west, &c) == -1)))
		|| ((c == 'S') && ((ft_mapreadch(map, &c) != 1)
				|| (c != 'O') || (ft_copypath(map, map->south, &c) == -1))))
		map_error("invalid path!");
}

void	map_load(char *cubfile)
{
	char	c;
	t_map3d	*map;

	open_cubfile(cubfile);
	map = getmap();
	while (ft_mapreadch(map, &c) == 1)
	{
		ft_skipcharset(map, &c, " \t\r\v\f\n");
		if ((c == 'F') && (ft_copycolor(map, &map->floor, &c) == -1))
			map_error("invalid floor color!");
		if ((c == 'C') && (ft_copycolor(map, &map->ceiling, &c) == -1))
			map_error("invalid ceiling color!");
		map_load_files(map);
		if (map->flags_number == MAX_FLAGS_NUMBER)
		{
			getmapsize(map);
			if ((map->width < 3) || (map->height < 3) || (map->players != 1))
				map_error("invalid map!");
			return (read_map_body(map));
		}
	}
	map_error("can't read all components!");
}

t_cub3d	*cub3d_parsing(int ac, char **av)
{
	static t_cub3d	cub;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit (EXIT_FAILURE);
	}
	map_load(av[1]);
	getmap()->player_speed = DEFAULT_PLAYER_SPEED;
	getmap()->player_rotation_angle = DEFAULT_PLAYER_ROTATION_ANGLE;
	return (&cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:23:57 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/07 20:21:34 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_copypath(t_map3d *map, char *dst, char *c)
{
	int	p;
	int	last_space_pos;

	if ((ft_mapreadch(map, c) != 1) || (!ft_isstab(*c) || (*dst != '\0')))
		return (-1);
	p = -1;
	last_space_pos = -1;
	ft_skipcharset(map, c, " \t");
	while ((*c != '\r') && (*c != '\n') && (*c != '\0') && (p < PATH_MAX))
	{
		dst[++p] = *c;
		if ((p > 0) && (!ft_strchr(" \t", dst[p - 1]))
			&& (ft_strchr(" \t\r\v\f\n", dst[p])))
			last_space_pos = p;
		ft_mapreadch(map, c);
	}
	if ((p < 1) || (last_space_pos >= PATH_MAX))
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

int	ft_atobyte(t_map3d *map, int n, char *c)
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
	ft_skipcharset(map, c, " \t");
	if ((p < 1) || (byte > 255) || ((n < 2) && (*c != ','))
		|| ((n == 2) && !ft_isline(*c)))
		map_error("Error: invalid color!");
	return (byte);
}

int	ft_copycolor(t_map3d *map, unsigned int *bgr, char *c)
{
	int	byte;
	int	n;

	if ((ft_mapreadch(map, c) != 1) || (!ft_isstab(*c) || (*bgr != 0)))
		return (-1);
	*bgr = 0x000000FF;
	n = 0;
	while (n < 3)
	{
		ft_skipcharset(map, c, " \t");
		byte = ft_atobyte(map, n, c);
		ft_skipcharset(map, c, " \t");
		*bgr |= (byte << 8 * (3 - n));
		if (!ft_isline(*c) && (ft_mapreadch(map, c) != 1))
			return (-1);
		n++;
	}
	map->flags_number++;
	return (0);
}

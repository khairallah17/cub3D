/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:43:50 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/04 15:45:29 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	pixels_rgba(int r, int g, int b, int a)
{
	return ((unsigned int)r << 24 | (unsigned int)g << 16 | (unsigned int)b << 8 | (unsigned int)a);
}

void	error_rgb_proba(char *temp, int i, int count_cama)
{
	while (temp[i])
	{
		if ((temp[i] < '0' || temp[i] > '9') && temp[i] != ',')
		{
			printf("ERROR: Please re-Check if RGB are Digits\n");
			exit(EXIT_FAILURE);
		}
		if (temp[i] == ',')
			count_cama++;
		if (temp[i] == ',' && (temp[i + 1] == ',' \
			|| temp[i + 1] == ' '))
		{
			printf("ERROR: There an error on parsing color RGB\n");
			exit(EXIT_FAILURE);
		}
		else if (count_cama >= 3 || temp[0] == ',' \
						|| temp[strlen(temp) - 1] == ',')
		{
			printf("ERROR: There an error on parsing\
			There is Problem with ','\n");
			exit(EXIT_FAILURE);
		}
		else if (temp[i] == ' ')
		{
			printf("ERROR: There an espace on the RGB color\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

unsigned int	send_rgb_color(char *temp, char **rgb_color)
{
	int	i;
	int	tb_color[3];

	i = 0;
	rgb_color = ft_split(temp, ',');
	if (rgb_color == NULL || !rgb_color[0] || !rgb_color[1] || !rgb_color[2])
	{
		printf("%s\n", "Error: Allocation are not being success");
		exit(EXIT_FAILURE);
	}
	while (i < 3)
	{
		tb_color[i] = ft_atoi(rgb_color[i]);
		if (tb_color[i] < 0 || tb_color[i] > 255)
		{
			printf("ERROR: Please re-change range of RGB the limit [0-255]\n");
			exit(EXIT_FAILURE);
		}
		free(rgb_color[i]);
		i++;
	}
	free(rgb_color);
	rgb_color = NULL;
	free(temp);
	temp = NULL;
	return (pixels_rgba(tb_color[0], tb_color[1], tb_color[2], 255));
}

unsigned int	check_color(t_cub3d *cub)
{
	int		first_index_color;
	int		second_index_color;
	unsigned int		color;
	char	*temp;
	char	**rgb_color;

	// printf("eeee = %s\n", cub->tmp_store);
	rgb_color = NULL;
	first_index_color = index_first_path(cub->tmp_store, 1);
	second_index_color = index_end_path(cub->tmp_store, (ft_strlen(cub->tmp_store) - 2));// - 3)); //----> tmp_store  at the end fiha '    \n\0' so len(tmp) - \n - \0 
	// printf("rrr1 = [%c]\n", cub->tmp_store[first_index_color]); //skipping "/0" + also first character and secend character space "F "
	// printf("rrr2 = [%c]\n", cub->tmp_store[second_index_color]); //skipping "/0" + also first character and secend character space "F "
	temp = ft_substr(cub->tmp_store, first_index_color, \
						(second_index_color - first_index_color + 1));
	// printf("rrr2 = [%s]\n", temp); //skipping "/0" + also first character and secend character space "F "
	if (!temp)
	{
		free(temp);
		temp = NULL;
		printf("ERROR: Please re-check if RGB color are not empty\n");
		exit(EXIT_FAILURE);
	}
	error_rgb_proba(temp, 0, 0);
	color = send_rgb_color(temp, rgb_color);
	// exit(1);
	cub->count_txtr_line++;
	return (color);
}

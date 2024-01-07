/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:48:56 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/07 05:51:22 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	index_first_path(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	index_end_path(char *str, int i)
{
	while (i >= 0 && str[i] == ' ')
		i--;
	return (i);
}

char	*search_path_texture(t_cub3d *cub)
{
	int		first_index_path;
	int		end_index_path;
	int		fd;
	char	*str;

	cub->count_txtr_line++;
	first_index_path = index_first_path(cub->tmp_store, 2);
	end_index_path = index_end_path(cub->tmp_store, strlen(cub->tmp_store) - 2);
	str = ft_substr(cub->tmp_store, first_index_path, \
		end_index_path - first_index_path + 1);
	if (!strnstr(str, ".xpm", strlen(str)) || \
			strncmp(strnstr(str, ".xpm", strlen(str)), ".xpm", strlen(".xpm")))
	{
		printf("Error: Path missed .xpm at the end\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		fd = open(str, O_RDWR);
		if (fd == -1)
		{
			printf("Error: can't Open and read path Texture\n");
			exit(EXIT_FAILURE);
		}
	}
	return (str);
}

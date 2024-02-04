/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:48:56 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/03 22:37:16 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	index_first_path(char *str, int i)
{
	// printf("www %s", str);
	while (str[i] && (str[i] == ' '))
		i++;
	return (i);
}

int	index_end_path(char *str, int i)
{
	while (i >= 0 && (str[i] == ' '))
		i--;
	// i++;
	return (i);
}

char	*search_path_texture(t_cub3d *cub)
{
	int		first_index_path;
	int		end_index_path;
	int		fd;
	char	*str;

	first_index_path = index_first_path(cub->tmp_store, 2);
	end_index_path = index_end_path(cub->tmp_store, strlen(cub->tmp_store) - 2);
	str = ft_substr(cub->tmp_store, first_index_path, \
		end_index_path - first_index_path + 1);
	if (!strnstr(str, ".png", strlen(str)) || \
			strncmp(strnstr(str, ".png", strlen(str)), ".png", strlen(".png")))
	{
		printf("Error: Path missed .png at the end\n");
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
	cub->count_txtr_line++;
	return (str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:30:25 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/04 15:39:54 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <stdint.h>

static void	initial_param(t_cub3d *get_parm, char *path_map)
{
	get_parm->prs_map.map.map_grid = NULL;
	get_parm->prs_map.map.width = 0;
	get_parm->prs_map.map.height = 0;
	get_parm->count_txtr_line = 0;
	get_parm->error_parse_nb = 0;
	get_parm->prs_map.f_c_color.floor = -1;
	get_parm->prs_map.f_c_color.ceiling = -1;
	get_parm->prs_map.texture.east = NULL;
	get_parm->prs_map.texture.north = NULL;
	get_parm->prs_map.texture.south = NULL;
	get_parm->prs_map.texture.west = NULL;
	get_parm->path_maps = strdup(path_map);
	get_parm->map_fd = open(get_parm->path_maps, O_RDONLY);
}

static void	print_check_err(t_cub3d *cub, char *str)
{
	int	i;

	i = 0;
	while (i < cub->prs_map.map.height)
	{
		free(cub->prs_map.map.map_grid[i]);
		cub->prs_map.map.map_grid[i++] = NULL;
	}
	if (i != 0)
	{
		free(cub->prs_map.map.map_grid);
		cub->prs_map.map.map_grid = NULL;
	}
	free(cub);
	cub = NULL;
	printf("%s", str);
	exit(EXIT_FAILURE);
}

static void	parse_texture(t_cub3d *cub)
{
	
	printf("colorc == %d\n",cub->prs_map.f_c_color.ceiling);
	if (!strncmp(cub->tmp_store, "NO ", 3) && !cub->prs_map.texture.north)
		cub->prs_map.texture.north = search_path_texture(cub);
	else if (!strncmp(cub->tmp_store, "SO ", 3) && !cub->prs_map.texture.south)
		cub->prs_map.texture.south = search_path_texture(cub);
	else if (!strncmp(cub->tmp_store, "WE ", 3) && !cub->prs_map.texture.west)
		cub->prs_map.texture.west = search_path_texture(cub);
	else if (!strncmp(cub->tmp_store, "EA ", 3) && !cub->prs_map.texture.east)
		cub->prs_map.texture.east = search_path_texture(cub);
	else if (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor == -1)
		cub->prs_map.f_c_color.floor = check_color(cub);
	else if (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling == -1)
		cub->prs_map.f_c_color.ceiling = check_color(cub);
	else if ((!strncmp(cub->tmp_store, "NO ", 3) && cub->prs_map.texture.north)
		|| (!strncmp(cub->tmp_store, "SO ", 3) && cub->prs_map.texture.south)
		|| (!strncmp(cub->tmp_store, "WE ", 3) && cub->prs_map.texture.west)
		|| (!strncmp(cub->tmp_store, "EA ", 3) && cub->prs_map.texture.east)
		|| (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor != -1)
		|| (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling != -1))
		cub->error_parse_nb = 1;
	else if (ft_strchr("01NSWE ", cub->tmp_store[0]))
		cub->error_parse_nb = -1;
	else
		cub->error_parse_nb = 2;
	printf("colorf == %d\n",cub->prs_map.f_c_color.floor);
}

void	send_err_free(t_cub3d *cub, int err_nbr, char *error_msg)
{
	if (err_nbr == -1)
		free(cub->tmp_store);
	free(cub->path_maps);
	if (cub->prs_map.texture.east != NULL)
		free(cub->prs_map.texture.east);
	if (cub->prs_map.texture.north != NULL)
		free(cub->prs_map.texture.north);
	if (cub->prs_map.texture.south != NULL)
		free(cub->prs_map.texture.south);
	if (cub->prs_map.texture.west != NULL)
		free(cub->prs_map.texture.west);
	print_check_err(cub, error_msg);
}

static void	check_for_errors(int idx_line, int count_txtr,
	int err_nbr, t_cub3d *cub)
{
	if (idx_line == 0 || (cub->tmp_store == NULL && count_txtr == 0))
		send_err_free(cub, err_nbr, "ERROR: Empty Map file");
	else if (err_nbr == 1)
		send_err_free(cub, err_nbr, "ERROR: There is Diplicated \
	Parameters Please Re-check");
	else if (err_nbr == 2)
		send_err_free(cub, err_nbr, "ERROR: Undifined character on the file");
	else if (count_txtr != 6)
	{
		printf("number texture == %d\n", count_txtr);
		send_err_free(cub, err_nbr, "ERROR: Missing One or \
		Multiples line parameter (NO,SO,WE,EA,F,C)");
	}
}

int	parsing_param_text_and_rm_newline(t_cub3d *cub)
{
	int	count_line;

	count_line = 0;
	cub->tmp_store = get_next_line(cub->map_fd);
	while (cub->tmp_store)
	{
		count_line++;
		if (!strncmp(cub->tmp_store, "\n", 1))
		{
			free(cub->tmp_store);
			cub->tmp_store = get_next_line(cub->map_fd);
			continue ;
		}
		parse_texture(cub);
		if (cub->error_parse_nb != -1)
			free(cub->tmp_store);
		if (cub->error_parse_nb)
			break ;
		cub->tmp_store = get_next_line(cub->map_fd);
	}
	check_for_errors(count_line,
		cub->count_txtr_line, cub->error_parse_nb, cub);
	return (count_line);
}

//fill map now
static void	remplir_map(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->tmp_store)
	{
		cub3d->prs_map.map.map_grid[i] = (char *)malloc(sizeof(char) *
				(cub3d->prs_map.map.width + 1));
		if (!cub3d->prs_map.map.map_grid[i])
			send_err_free(cub3d, -1, \
			"Error: Allocation are not being success1");
		j = 0;
		while (cub3d->tmp_store[j] != '\0' && cub3d->tmp_store[j] != '\n')
		{
			cub3d->prs_map.map.map_grid[i][j] = cub3d->tmp_store[j];
			j++;
		}
		while(j < cub3d->prs_map.map.width) // sparate it with space
		    cub3d->prs_map.map.map_grid[i][j++] = ' ';
		cub3d->prs_map.map.map_grid[i][j] = '\0';
		i++;
		free(cub3d->tmp_store); // free last buffer
		cub3d->tmp_store = get_next_line(cub3d->map_fd);
	}
	cub3d->prs_map.map.map_grid[i] = NULL;
}

static void	skip_texture_and_remplir_map(t_cub3d *cub3d, int *line_count)
{
	// fill map
	cub3d->map_fd = open(cub3d->path_maps, O_RDONLY);
	cub3d->tmp_store = get_next_line(cub3d->map_fd);
	printf("line = %d\n", (*line_count));
	// skip 6 line of texture
	while(cub3d->tmp_store && (*line_count) > 1)
	{
		(*line_count)--;
		free(cub3d->tmp_store);
		cub3d->tmp_store = get_next_line(cub3d->map_fd);
	}
	cub3d->prs_map.map.map_grid = (char **)malloc(sizeof(char *) \
		* (cub3d->prs_map.map.height + 1));
	if (!cub3d->prs_map.map.map_grid)
		send_err_free(cub3d, -1, "Error: Allocation are not being success");
	printf("%p\n", cub3d->prs_map.map.map_grid);
	remplir_map(cub3d);
}

t_cub3d	*parsing(int ac, char **av)
{
	t_cub3d	*cub;
	int		count_line;

	check_arguments(ac, av);
	cub = (t_cub3d *)malloc(sizeof(t_cub3d));
	initial_param(cub, av[1]);
	count_line = parsing_param_text_and_rm_newline(cub);
	while (cub->tmp_store)
	{
		if (((int)ft_strlen(cub->tmp_store) > cub->prs_map.map.width)
			&& cub->tmp_store[((int)ft_strlen(cub->tmp_store) - 1)] == '\n')
			cub->prs_map.map.width = (int)ft_strlen(cub->tmp_store) - 1;
		else if (((int)ft_strlen(cub->tmp_store) > cub->prs_map.map.width)
			&& cub->tmp_store[((int)ft_strlen(cub->tmp_store) - 1)] != '\n')
			cub->prs_map.map.width = (int)ft_strlen(cub->tmp_store);
		cub->prs_map.map.height++;
		free(cub->tmp_store);
		cub->tmp_store = get_next_line(cub->map_fd);
	}
	close(cub->map_fd);
	skip_texture_and_remplir_map(cub, &count_line);
	return (cub);
}

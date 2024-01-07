/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:41:25 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/07 05:42:05 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_arguments(int ac, char **av)
{
	int	fd;

	if (ac == 1)
	{
		write (2, "Error: Check please should be exact \
		<EXECUTABLE> + <MAP_NAME.CUB>\n", 67);
		exit (EXIT_FAILURE);
	}
	else if (ac > 2)
	{
		write (2, "Error: There is too many arguments \
		please re-check with <EXECUTABLE> + <MAP_NAME.CUB>\n", 87);
		exit (EXIT_FAILURE);
	}
	else if (ac == 2 && (!strnstr(av[1], ".cub", strlen(av[1])) \
		|| strncmp(strnstr(av[1], ".cub", strlen(av[1])), ".cub", 5)))
	{
		write (2, "Error: In Map Reading it should be <MAP_NAME.CUB>\n", 52);
		exit (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Check please for map (Unable to open map file)");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

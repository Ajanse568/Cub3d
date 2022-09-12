/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rgb_to_hex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:17 by ajanse        #+#    #+#                 */
/*   Updated: 2022/09/12 14:42:07 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int	convert_rgb_to_hex(char **rgb)
{
	int	r;
	int	g;
	int	b;
	int	result;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		exit_program("The rgb codes for the ceiling \
		or the floor are not correct.\n");
	result = (r * pow(10, 4)) + (g * pow(10, 2)) + b;
	return (result);
}

void	floor_ceiling_to_hex(t_parse *parse, t_map *map_conf)
{
	char	**rgb_floor;
	char	**rgb_ceiling;

	rgb_floor = ft_split(parse->floor, ',');
	rgb_ceiling = ft_split(parse->ceiling, ',');
	map_conf->floor = convert_rgb_to_hex(rgb_floor);
	map_conf->ceiling = convert_rgb_to_hex(rgb_ceiling);
	free_ptrarray(rgb_floor);
	free_ptrarray(rgb_ceiling);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rgb_to_hex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:17 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/15 13:54:36 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

void	check_legal_rgb(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if ((rgb[i][j] > '9' || rgb[i][j] < '0') || j > 2)
				exit_program("Rgb values are incorrect.");
			j++;
		}
		i++;
	}
}

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

	rgb_floor = protect(ft_split(parse->floor, ','));
	rgb_ceiling = protect(ft_split(parse->ceiling, ','));
	check_legal_rgb(rgb_floor);
	check_legal_rgb(rgb_ceiling);
	map_conf->floor = convert_rgb_to_hex(rgb_floor);
	map_conf->ceiling = convert_rgb_to_hex(rgb_ceiling);
	free_ptrarray(rgb_floor);
	free_ptrarray(rgb_ceiling);
}

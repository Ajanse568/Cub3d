/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:11 by ajanse        #+#    #+#                 */
/*   Updated: 2022/09/12 14:23:00 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdio.h>

char	*get_texture(t_parse *parse, int i, int j, int skip_name)
{
	char	*texture;

	if (skip_name == 1)
		j += 1;
	if (skip_name == 2)
		j += 2;
	while (!ft_isalnum(parse->args[i][j]))
		j++;
	texture = ft_substr_free(parse->args[i], j, ft_strlen(parse->args[i]));
	parse->count_args++;
	return (texture);
}

void	tex_checker(t_parse *parse, int i, int j)
{
	if (parse->args[i][j] == 'N' && parse->args[i][j + 1] == 'O')
		parse->walls[0] = get_texture(parse, i, j, 2);
	if (parse->args[i][j] == 'S' && parse->args[i][j + 1] == 'O')
		parse->walls[1] = get_texture(parse, i, j, 2);
	if (parse->args[i][j] == 'W' && parse->args[i][j + 1] == 'E')
		parse->walls[2] = get_texture(parse, i, j, 2);
	if (parse->args[i][j] == 'E' && parse->args[i][j + 1] == 'A')
		parse->walls[3] = get_texture(parse, i, j, 2);
	if (parse->args[i][j] == 'F')
		parse->floor = get_texture(parse, i, j, 1);
	if (parse->args[i][j] == 'C')
		parse->ceiling = get_texture(parse, i, j, 1);
}

void	read_textures(t_parse *parse)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (parse->count_args < 6)
	{
		j = 0;
		while (parse->args[i][j])
		{
			tex_checker(parse, i, j);
			j++;
		}
		i++;
	}
	printf("%s\n", parse->walls[0]);
	parse->i = i;
}

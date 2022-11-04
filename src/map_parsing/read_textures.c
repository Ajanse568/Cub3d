/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:11 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/04 11:17:14 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

char	*get_texture(t_parse *parse, int i, int j, int skip_name)
{
	char	*texture;

	while (!ft_isalnum(parse->args[i][j]))
		j++;
	if (skip_name == 1)
		j += 1;
	if (skip_name == 2)
		j += 2;
	while (!ft_isalnum(parse->args[i][j]))
		j++;
	texture = ft_substr_free(parse->args[i], j, ft_strlen(parse->args[i]));
	return (texture);
}

void	tex_checker(t_parse *parse)
{
	char	*wind;
	int		j;
	int		i;

	wind = "NOSOWEEA";
	j = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (parse->args[j])
		{
			if (!ft_strncmp(wind + i * 2, parse->args[j], 2))
			{
				parse->walls[i] = get_texture(parse, j, 0, 2);
				parse->count_args++;
			}
			j++;
		}
		i++;
	}
	if (parse->count_args > 4)
		exit_program("Too many argument!");
}

int	check_floor_and_ceiling(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse->args[i])
	{
		j = 0;
		while (parse->args[i][j])
		{
			if (parse->args[i][j] == 'F')
			{
				parse->f_check++;
				parse->floor = get_texture(parse, i, j, 1);
			}
			if (parse->args[i][j] == 'C')
			{
				parse->c_check++;
				parse->ceiling = get_texture(parse, i, j, 1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

int	get_map_beginning(t_parse *parse)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (parse->args[i] && count < 5)
	{
		j = 0;
		while (parse->args[i][j])
		{
			if ((parse->args[i][j] == 'N' && parse->args[i][j + 1] == 'O') ||
				(parse->args[i][j] == 'S' && parse->args[i][j + 1] == 'O') ||
				(parse->args[i][j] == 'W' && parse->args[i][j + 1] == 'E') ||
				(parse->args[i][j] == 'E' && parse->args[i][j + 1] == 'A') ||
				(parse->args[i][j] == 'F') || (parse->args[i][j] == 'C'))
					count++;
			j++;
		}
		i++;
	}
	return (i);
}

void	read_textures(t_parse *parse)
{
	int	i;

	i = 0;
	check_floor_and_ceiling(parse);
	if (parse->f_check != 1 || parse->c_check != 1)
		exit_program("Invalid floor or ceiling arguments.");
	parse->i = get_map_beginning(parse);
	tex_checker(parse);
	i = 0;
	while (i < 4)
	{
		if (!parse->walls[i])
			exit_program("Missing argument!");
		i++;
	}
}

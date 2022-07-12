#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	get_position(t_parse *parse, t_frame *frame, int i, int j)
{
	if (parse->map[i][j] == 'N' || parse->map[i][j] == 'S' || parse->map[i][j] == 'E' || parse->map[i][j] == 'W')
	{
		frame->pl->px = j * 64.0;
		frame->pl->py = i * 64.0;
		if (parse->map[i][j] == 'N')
			frame->pl->pa = 90.0;
		if (parse->map[i][j] == 'S')
			frame->pl->pa = 270.0;
		if (parse->map[i][j] == 'E')
			frame->pl->pa = 0.0;
		if (parse->map[i][j] == 'W')
			frame->pl->pa = 180.0;
		frame->pl->pdx = cos(degToRad(frame->pl->pa));
		frame->pl->pdy = -sin(degToRad(frame->pl->pa));
	}
}

int	check_valid_characters_map(t_parse *parse, t_map map_conf)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < map_conf.map_height)
	{
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == 'N' || parse->map[i][j] == 'S' || \
				parse->map[i][j] == 'E' || parse->map[i][j] == 'W')
				count++;
			else if (parse->map[i][j] != '1' && \
				parse->map[i][j] != '0' && parse->map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	if (count > 1 || count < 1)
		return (1);
	return (0);
}

// int	check_spaces(t_parse *parse)
// {
// 	int	i;
// 	int	j;
// 	int	check;

// 	i = parse->i;
// 	while (parse->args[i])
// 		printf("%s\n", parse->args[i++]);
// 	while (parse->args[i])
// 	{
// 		j = 0;
// 		check = 0;
// 		while (parse->args[i][j])
// 		{
// 			if (parse->args[i][j] != ' ')
// 				check = 1;
// 			j++;
// 		}
// 		if (check == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }



int	search_newline(char *str, int i)
{
	while (str[i] != '\n')
		i++;
	while (str[i] != '1')
		i++;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	check_newline_map(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == 'N' && str[i + 1] == 'O') || \
		(str[i] == 'S' && str[i + 1] == 'O') || \
		(str[i] == 'W' && str[i + 1] == 'E') || \
		(str[i] == 'E' && str[i + 1] == 'A') || \
		(str[i] == 'F') || (str[i + 1] == 'C'))
			count++;
		if (count == 6)
			break;
		i++;
	}
	i++;
	if (search_newline(str, i))
		return (1);
	return (0);
}
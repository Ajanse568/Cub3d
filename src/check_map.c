#include "cub3d.h"
#include "libft.h"

int	check_elementes(t_parse *parse, int i, int j)
{
	if ((parse->args[i][j] != 'N' && parse->args[i][j + 1] != 'O') && \
		(parse->args[i][j] != 'S' && parse->args[i][j + 1] != 'O') && \
		(parse->args[i][j] != 'W' && parse->args[i][j + 1] != 'E') && \
		(parse->args[i][j] != 'E' && parse->args[i][j + 1] != 'A') && \
		(parse->args[i][j] != 'F') && (parse->args[i][j] != 'C'))
		return (1);
	else
	{
		parse->count_args++;
		return (0);
	}
}

int	check_elements_on_top(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse->args[i][j])
	{
		j = 0;
		while (parse->args[i][j] != '\n')
		{
			if (ft_isalnum(parse->args[i][j]))
			{
				if (parse->count_args == 6)
					return (0);
				if (check_elementes(parse, i, j))
					return (1);
				else
					break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_top_bottom_border(t_parse *parse, int i , int j)
{
	if (ft_isalnum(parse->map[i][j]))
	{
		if (parse->map[i][j] != '1')
			return (1);
	}
	return (0);
}

int	check_middle_border(t_parse *parse, int i, int j)
{
	if (j == 0 && ft_isalnum(parse->map[i][j]))
		if (parse->map[i][j] != '1')
			return (1);
	if (j == (int)ft_strlen(parse->map[i]) - 1 && ft_isalnum(parse->map[i][j]))
		if (parse->map[i][j] != '1')
			return (1);
	if (parse->map[i][j] != '1' && parse->map[i][j] != '0')
		return (0);
	if ((parse->map[i - 1][j] != '1' && parse->map[i - 1][j] != '0' ) || \
		(parse->map[i + 1][j] != '1' && parse->map[i + 1][j] != '0' ) || \
		(parse->map[i][j - 1] != '1' && parse->map[i][j - 1] != '0' ) || \
		(parse->map[i][j + 1] != '1' && parse->map[i][j + 1] != '0'))
	{
		if (ft_isalpha(parse->map[i + 1][j]) || \
			ft_isalpha(parse->map[i - 1][j]) || \
			ft_isalpha(parse->map[i][j + 1]) || \
			ft_isalpha(parse->map[i][j - 1]))
			return (0);
		if (parse->map[i][j] != '1')
			return (1);
	}
	return (0);
}

int	check_borders(t_parse *parse, t_frame *frame)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)frame;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			get_position(parse, frame, i, j);
			if (i == 0 || i == parse->height_map)
			{
				if (check_top_bottom_border(parse, i, j))
					return (1);
			}
			else
				if (check_middle_border(parse, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}
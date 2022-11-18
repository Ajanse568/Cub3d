/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:06 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/15 13:53:51 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	read_args(t_parse *parse, char *file_name)
{
	int		fd;
	int		check;
	int		read_return;

	read_return = 1;
	check = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_program("Could not open map.");
	while (read_return != 0)
	{
		read_return = read(fd, parse->ch, 1);
		if (read_return == -1)
			exit_program("A read error occured.\n");
		if (!check)
			parse->str = protect(ft_strdup(parse->ch));
		else
			parse->str = ft_strjoin_free(parse->str, parse->ch);
		check = 1;
	}
	parse->str[ft_strlen(parse->str) - 1] = '\0';
	if (check_newline_map(parse->str))
		exit_program("The map or the arguments are incorrect.\n");
	parse->args = protect(ft_split(parse->str, '\n'));
	return (0);
}

void	make_map(t_parse *parse, t_frame *frame)
{
	int	i;
	int	k;

	(void)frame;
	i = parse->i;
	k = 0;
	while (parse->args[parse->i])
	{
		if (!parse->args[parse->i])
			parse->i++;
		if (parse->args[parse->i])
			break ;
	}
	i = parse->i;
	while (parse->args[i])
		i++;
	parse->map = protect(ft_calloc((i - parse->i) + 2, sizeof(char *)));
	while (parse->args[parse->i])
	{
		parse->map[k] = protect(ft_strdup(parse->args[parse->i]));
		parse->i++;
		k++;
	}
}

char	*conv_to_arr(char **map_d)
{
	int		len;
	int		line_len;
	int		i;
	char	*map;

	len = arrlen(map_d);
	line_len = linelen(map_d);
	map = protect(ft_calloc(len * line_len + 1, sizeof(char)));
	i = 0;
	while (i < len)
	{
		ft_strlcpy(&map[i * line_len], map_d[i], line_len);
		i++;
	}
	return (map);
}

void	parsing(t_parse *parse, t_frame *frame, char *file_name)
{
	read_args(parse, file_name);
	if (check_elements_on_top(parse))
		exit_program("The given arguments are invalid.\n");
	parse->count_args = 0;
	read_textures(parse);
	make_map(parse, frame);
	get_height_and_width(parse, frame);
	if (check_borders(parse, frame))
		exit_program("Map is invalid.\n");
	if (check_valid_characters_map(parse, *frame->map_conf))
		exit_program("Map is invalid.\n");
	floor_ceiling_to_hex(parse, frame->map_conf);
	frame->map_conf->map = conv_to_arr(parse->map);
}

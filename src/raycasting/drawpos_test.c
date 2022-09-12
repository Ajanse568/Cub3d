/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawpos_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:22:50 by ajanse        #+#    #+#                 */
/*   Updated: 2022/09/12 13:56:27 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_column(int y, int line_h, float steps, t_draw dr)
{
	int		i;
	float	wall_y;

	while (dr.li.width > 0)
	{
		dr.li.width--;
		i = 0;
		wall_y = 0;
		while (i < line_h)
		{
			draw_pixel(dr.img, dr.li.pos + dr.li.width, y + i, \
			get_color(dr.wall, dr.wall_x, (64 / 2) + (int)wall_y));
			draw_pixel(dr.img, dr.li.pos + dr.li.width, y - i, \
			get_color(dr.wall, dr.wall_x, (64 / 2) - (int)wall_y));
			i++;
			wall_y += steps;
		}
		while (i < 250)
		{
			draw_pixel(dr.img, dr.li.pos + dr.li.width, y + i, dr.floor);
			draw_pixel(dr.img, dr.li.pos + dr.li.width, y - i, dr.ceiling);
			i++;
		}
	}
}

void	draw_line(t_draw dr)
{
	int		y;
	int		line_h;
	float	steps;

	y = 500 / 2;
	line_h = y * (1.5 * 64 / dr.dist);
	steps = 32. / line_h;
	if (line_h > 250)
		line_h = 250;
	draw_column(y, line_h, steps, dr);
}

void	draw_wall(t_line li, t_data *walls, t_map map_conf, t_data *img)
{
	t_draw	dr;

	dr.dist = li.ray.dist;
	dr.li = li;
	dr.floor = map_conf.floor;
	dr.ceiling = map_conf.ceiling;
	dr.img = img;
	if (li.h_or_v)
	{
		dr.wall_x = (int)li.ray.fy % 64;
		dr.wall = walls + 2;
		if (li.ra < 90 || li.ra > 270)
			dr.wall++;
	}
	else
	{
		dr.wall_x = (int)li.ray.fx % 64;
		dr.wall = walls;
		if (li.ra > 180)
			dr.wall++;
	}
	draw_line(dr);
}

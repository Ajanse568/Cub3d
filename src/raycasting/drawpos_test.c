/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawpos_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:22:50 by ajanse        #+#    #+#                 */
/*   Updated: 2022/09/07 15:19:47 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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

void	draw_line(t_draw dr)
{
	int		y;
	int		lineH;
	float	steps;
	int		i;
	float	wall_y;

	y = 500 / 2;
	lineH = y * (1.5 * 64 / dr.dist);
	steps = 32. / lineH;
	//max_height
	if (lineH > 250)
		lineH = 250;
	while (dr.li.width > 0)
	{
		dr.li.width--;
		i = 0;
		wall_y = 0;
		while (i < lineH)
		{
			my_mlx_pixel_put(dr.img, dr.li.pos + dr.li.width, y + i, get_color(dr.wall, dr.wall_x, (64 / 2) + (int)wall_y));
			my_mlx_pixel_put(dr.img, dr.li.pos + dr.li.width, y - i, get_color(dr.wall, dr.wall_x, (64 / 2) - (int)wall_y));
			i++;
			wall_y += steps;
		}
		while(i < 250)
		{
			my_mlx_pixel_put(dr.img, dr.li.pos + dr.li.width, y + i, dr.floor);
			my_mlx_pixel_put(dr.img, dr.li.pos + dr.li.width, y - i, dr.ceiling);
			i++;
		}
	}
}

void	draw_wall(t_line li, t_data *walls, t_data *img)
{
	t_draw	dr;

	dr.dist = li.ray.dist;
	dr.li = li;
	dr.floor = 0x0032A840;
	dr.ceiling = 0x00ADD8E6;
	dr.img = img;
	if (li.h_or_v)
	{
		dr.wall_x = (int)li.ray.fy % 64;
		dr.wall = walls + 2;
	}
	else
	{
		dr.wall_x = (int)li.ray.fx % 64;
		dr.wall = walls;
	}
	draw_line(dr);
}

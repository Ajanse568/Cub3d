/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:22:50 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/05 17:42:08 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	draw_square(int px, int py, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 16)
		{
			my_mlx_pixel_put(img, px * 16 + 960 + x, py * 16 + y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	draw_square_outline(int px, int py, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 16)
		{
			if (x < 2 || x > 98 || y < 2 || y > 98)
				my_mlx_pixel_put(img, px * 16 + 960 + x, py * 16 + y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	draw_grid(t_data *img, int *map, int px, int py)
{
	int	x;
	int	y;

	(void)px;
	(void)py;
	x = 0;
	if (x < 0)
		x = 0;
	while (x < 8)
	{
		y = 0;
		while(y < 16)
		{
			if (map[y * 8 + x])
				draw_square(x, y, img);
			// else 
			// 	draw_square_outline(x, y, img);
			y++;
		}
		x++;
	}
}

void	draw_angle(t_data *img, int radius, t_player pl)
{
	pl.px = pl.px + (pl.pdx * (radius + 50));
	pl.py = pl.py + (pl.pdy * (radius + 50));
	draw_player(img, &pl, 5);
}

void	draw_circle(t_data *img, int px, int py, int radius)
{
	int	sx;
	int	sy;
	int	x;
	int	y;
	int	sumsqr;

	x = px - radius;
	while (x < (px + radius))
	{
		y = py - radius;
		while (y < (py + radius))
		{
			sx = x - (px);
			sy = y - (py);
			sumsqr = sy * sy + sx * sx;
			if (sumsqr < (radius * radius))
				my_mlx_pixel_put(img, x, y, 0x00FFFF00);
			y++;
		}
		x++;
	}
}

void	draw_player(t_data *img, t_player *pl, int radius)
{
	int	sx;
	int	sy;
	int	x;
	int	y;
	int	sumsqr;

	x = pl->px - radius;
	while (x < (pl->px + radius))
	{
		y = pl->py - radius;
		while (y < (pl->py + radius))
		{
			sx = x - (pl->px);
			sy = y - (pl->py);
			sumsqr = sy * sy + sx * sx;
			if (sumsqr < (radius * radius))
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}

void	draw_line(int dist, int wall_x, int line, t_data *wall, t_data *img)
{
	int		x;
	int		y;
	int		lineH;
	float	steps;
	int		i;
	int		c = 0;
	float	wall_y;

	x = line * 1;
	y = 500 / 2;
	lineH = y * (1.5 * 64 / dist);
	steps = 32. / lineH;
	if (lineH > 250)
		lineH = 250;
	while (c < 1)
	{
		i = 0;
		wall_y = 0;
		while (i < lineH)
		{
			my_mlx_pixel_put(img, x + c, y + i, get_color(wall, wall_x, (64 / 2) + (int)wall_y));
			my_mlx_pixel_put(img, x + c, y - i, get_color(wall, wall_x, (64 / 2) - (int)wall_y));
			i++;
			wall_y += steps;
		}
		while(i < 250)
		{
			my_mlx_pixel_put(img, x + c, y + i, 0x0032A840);//floor
			my_mlx_pixel_put(img, x + c, y - i, 0x00ADD8E6);//ceiling
			i++;
		}
		c++;
	}
}
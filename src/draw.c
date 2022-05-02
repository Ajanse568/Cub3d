/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:22:50 by ajanse        #+#    #+#                 */
/*   Updated: 2022/05/02 17:26:09 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

// int map[] =           //the map array. Edit to change level but keep the outer walls
// {
//  1,1,1,1,1,1,1,1,
//  1,0,1,0,0,0,0,1,
//  1,0,1,0,0,1,0,1,
//  1,0,1,0,0,0,0,1,
//  1,0,0,0,0,0,0,1,
//  1,0,0,0,0,0,0,1,
//  1,0,0,0,0,0,0,1,
//  1,1,1,1,1,1,1,1,	
// };

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(int px, int py, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(img, px * 100 + x, py * 100 + y, 0x000000FF);
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
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			if (x < 2 || x > 98 || y < 2 || y > 98)
				my_mlx_pixel_put(img, px * 100 + x, py * 100 + y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	draw_grid(t_data *img, int *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < 8)
	{
		y = 0;
		while(y < 8)
		{
			if (map[y * 8 + x])
				draw_square(x, y, img);
			else 
				draw_square_outline(x, y, img);
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
	if (radius > 6)
		draw_angle(img, radius, *pl);
}

void	draw_line(int dist, int color, int line, t_data *img)
{
	int	x;
	int	y;
	int	lineH;
	int	i = 0;
	int	c = 0;

	x = 900 + line * 15;
	y = 800 / 2;
	lineH = 400 - 400 * (dist / 900.0);
	printf("line:%i dist:%f lineH: %i\n", line, dist / 1142.0, lineH);
	while (c < 15)
	{
		i = 0;
		while (i < lineH)
		{
			my_mlx_pixel_put(img, x + c, y + i, color);
			my_mlx_pixel_put(img, x + c, y - i, color);
			i++;
		}
		c++;
	}
}
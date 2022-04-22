/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:22:50 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/22 17:39:52 by ajanse        ########   odam.nl         */
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

void	draw_grid(t_data *img)
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


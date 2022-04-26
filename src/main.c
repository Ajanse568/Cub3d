/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:21 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/26 09:27:56 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int map[] =           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

int	render_frame(t_frame *frame)
{
	t_data	img;

	img.img = mlx_new_image(frame->mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
								&img.line_length, &img.endian);
	draw_grid(&img, frame->map);
	draw_player(&img, frame->pl, 15);
	mlx_put_image_to_window(frame->mlx, frame->mlx_win, img.img, 0, 0);
	mlx_destroy_image(frame->mlx, img.img);
	return (0);
}

int	deal_key(int keycode, t_player *pl)
{
	int	pm;
	int	pm2;

	pm = (keycode == C_L || keycode == W || keycode == A) ? 1 : -1;
	pm2 = (keycode == W || keycode == D) ? 1 : -1;
	if (keycode == ESC)
		exit(0);
	if (keycode == C_L || keycode == C_R)
	{
		pl->pa += 5 * pm;
		pl->pa = FixAng(pl->pa);
		pl->pdx = cos(degToRad(pl->pa));
		pl->pdy = -sin(degToRad(pl->pa));
	}
	if (keycode == W || keycode == S)
	{
		pl->px += pm * pl->pdx * 5;
		pl->py += pm2 * pl->pdy * 5;
	}
	if (keycode == A || keycode == D)
	{
		pl->px += pm * pl->pdy * 5;
		pl->py += pm2 * pl->pdx * 5;
	}
	return (0);
}

t_player	*cub_init(void)
{
	t_player	*pl;

	pl = malloc(sizeof(t_player));
	if (!pl)
		return (0);
	pl->px = 450;
	pl->py = 450;
	pl->pa = 55;
	pl->pdx = cos(degToRad(pl->pa));
	pl->pdy = -sin(degToRad(pl->pa));
	return (pl);
}

int	main(void)
{
	t_frame	frame;

	frame.map = map;
	frame.mlx = mlx_init();
	frame.mlx_win = mlx_new_window(frame.mlx, 1920, 1080, "Hello world!");
	frame.pl = cub_init();
	mlx_hook(frame.mlx_win, 2, 0L, deal_key, frame.pl);
	mlx_hook(frame.mlx_win, 2, 0L, deal_key, frame.pl);
	mlx_loop_hook(frame.mlx, render_frame, &frame);
	mlx_loop(frame.mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:21 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/05 15:05:14 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int	render_frame(t_frame *frame)
{
	t_data	img;
	t_data	minimap;

	img.img = mlx_new_image(frame->mlx, 960, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
								&img.line_length, &img.endian);
	minimap.img = mlx_new_image(frame->mlx, 8 * 16, 8 * 16);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel, \
								&minimap.line_length, &minimap.endian);
	if (!check_keys(frame->key, W))
		move_player(frame->key, frame->pl, frame->map);
	if (!check_keys(frame->key, C_L))
		turn_player(frame->key, frame->pl);
	//draw_grid(&minimap, frame->map, frame->pl->px, frame->pl->py);
	//draw_player(&img, frame->pl, 15);
	raycast(*frame->pl, frame->map, &img, frame->wall);
	mlx_put_image_to_window(frame->mlx, frame->mlx_win, img.img, 0, 0);
	mlx_destroy_image(frame->mlx, img.img);
	return (0);
}

t_player	*cub_init(t_key *key)
{
	t_player	*pl;

	pl = malloc(sizeof(t_player));
	if (!pl)
		return (0);
	pl->px = 150;
	pl->py = 345;
	pl->pa = 90;
	pl->pdx = cos(degToRad(pl->pa));
	pl->pdy = -sin(degToRad(pl->pa));
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->c_l = 0;
	key->c_r = 0;
	return (pl);
}

int	main(int argc, char *argv[])
{
	t_frame	frame;
	t_key	key;
	t_parse parse;
	int		i = 64;

	(void)argc;
	init_parse(&parse);
	frame.pl = cub_init(&key);
	parsing(&parse, &frame, argv[1]);
	// frame.map = map;
	frame.mlx = mlx_init();
	frame.mlx_win = mlx_new_window(frame.mlx, 960 + 64 * 8, 500, "Cub3d");
	frame.key = &key;
	frame.wall.img = mlx_xpm_file_to_image(frame.mlx, "textures/wall_3.xpm", &i, &i);
	frame.wall.addr = mlx_get_data_addr(frame.wall.img, &frame.wall.bits_per_pixel, \
										&frame.wall.line_length, &frame.wall.endian);
	mlx_hook(frame.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &key);
	mlx_hook(frame.mlx_win, X_EVENT_KEY_RELEASE, 0, &key_release, &key);
	mlx_hook(frame.mlx_win, 17, 0, red_cross, &key);
	//render_frame(&frame);
	mlx_loop_hook(frame.mlx, render_frame, &frame);
	mlx_loop(frame.mlx);
}

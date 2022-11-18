/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:21 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/18 08:57:21 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	render_frame(t_frame *frame)
{
	t_data	img;

	img.img = mlx_new_image(frame->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
								&img.line_length, &img.endian);
	if (!check_keys(frame->key, W))
		move_player(frame->key, frame->pl, frame->map_conf);
	if (!check_keys(frame->key, C_L))
		turn_player(frame->key, frame->pl);
	cast_rays(*frame->pl, *frame->map_conf, &img);
	mlx_put_image_to_window(frame->mlx, frame->mlx_win, img.img, 0, 0);
	mlx_destroy_image(frame->mlx, img.img);
	return (0);
}

t_player	*cub_init(t_key *key)
{
	t_player	*pl;

	pl = protect(malloc(sizeof(t_player)));
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->c_l = 0;
	key->c_r = 0;
	return (pl);
}

void	load_walls(t_data *walls, t_parse parse, t_frame frame)
{
	int	i;
	int	x;

	x = 64;
	i = 0;
	while (i < 4)
	{
		walls[i].img = mlx_xpm_file_to_image(frame.mlx, parse.walls[i], &x, &x);
		if (walls[i].img == NULL)
			exit_program("Texture is not valid.");
		walls[i].addr = mlx_get_data_addr(walls[i].img, \
		&walls[i].bits_per_pixel, &walls[i].line_length, &walls[i].endian);
		i++;
	}
}

void	check_textures(t_parse parse)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = open(parse.walls[i], O_RDONLY);
		if (fd < 0)
			exit_program("Texturefile could not be opened.");
		else
			close(fd);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_frame	frame;
	t_map	map_conf;
	t_key	key;
	t_parse	parse;

	(void)argc;
	init_parse(&parse);
	frame.pl = cub_init(&key);
	frame.key = &key;
	frame.map_conf = &map_conf;
	parsing(&parse, &frame, argv[1]);
	check_textures(parse);
	frame.mlx = mlx_init();
	load_walls(frame.map_conf->walls, parse, frame);
	frame.mlx_win = mlx_new_window(frame.mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_hook(frame.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &key);
	mlx_hook(frame.mlx_win, X_EVENT_KEY_RELEASE, 0, &key_release, &key);
	mlx_hook(frame.mlx_win, 17, 0, red_cross, &key);
	mlx_loop_hook(frame.mlx, render_frame, &frame);
	mlx_loop(frame.mlx);
}

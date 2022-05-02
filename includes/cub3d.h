/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:14 by ajanse        #+#    #+#                 */
/*   Updated: 2022/05/02 16:39:51 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_player{
	float	px;
	float	py;
	int		pa;
	float	pdx;
	float	pdy;
}				t_player;

typedef struct	s_frame {
	t_player	*pl;
	void		*mlx;
	void		*mlx_win;
	int			*map;
}				t_frame;

typedef struct	s_ray {
	float	fx;
	float	fy;
	float	ya;
	float	xa;
}				t_ray;

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define C_L 123
# define C_R 124

void	draw_circle(t_data *img, int px, int py, int radius);
void	draw_player(t_data *img, t_player *pl, int radius);
float	degToRad(int a);
int		FixAng(int a);
void	draw_grid(t_data *img, int *map);
void	raycast(t_player pl, int *map, t_data *img);
void	draw_line(int dist, int color, int line, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
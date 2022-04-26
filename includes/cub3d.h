/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:14 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/26 09:27:14 by ajanse        ########   odam.nl         */
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
	int	fx;
	int	fy;
	int	ya;
	int	xa;
}				t_ray;

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define C_L 123
# define C_R 124

void	draw_player(t_data *img, t_player *pl, int radius);
float	degToRad(int a);
int		FixAng(int a);
void	draw_grid(t_data *img, int *map);
int		raycast(t_player pl, int *map);

#endif
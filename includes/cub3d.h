/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:14 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/05 15:08:57 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct	s_parse {
	char	*ch;
	char	*str;
	char	**args;
	char	**map;
	int		count_args;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
	int		i;
	int		width_map;
	int		height_map;
}				t_parse;

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
	float	pa;
	float	pdx;
	float	pdy;
}				t_player;

typedef struct	s_key {
	int	w;
	int	a;
	int	s;
	int	d;
	int	c_l;
	int	c_r;
}				t_key;

typedef struct	s_frame {
	t_player	*pl;
	void		*mlx;
	void		*mlx_win;
	char		*map;
	t_data		wall;
	t_key		*key;
}				t_frame;

typedef struct	s_ray {
	float	fx;
	float	fy;
	float	ya;
	float	xa;
	float	dist;
}				t_ray;

# define ESC					53
# define W						13
# define A						0
# define S						1
# define D						2
# define C_L					123
# define C_R					124
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3

void	draw_circle(t_data *img, int px, int py, int radius);
void	draw_player(t_data *img, t_player *pl, int radius);
float	degToRad(float a);
float	FixAng(float a);
void	draw_grid(t_data *img, int *map, int px, int py);
void	raycast(t_player pl, char *map, t_data *img, t_data wall);
//void	draw_line(int dist, int color, int line, t_data *img);
void	draw_line(int dist, int wall_x, int line, t_data *wall, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_ray(t_data *img, t_player pl, t_ray ray);
void	draw_wall(int dist, int wall_x, int line, t_data wall, t_data *img);
void	exit_program(char *exit_message);
char	*ft_substr_free(char const *s, unsigned int start, unsigned int len);
void	get_height_and_width(t_parse *parse);

//Parsing
void	init_parse(t_parse *parse);
void	parsing(t_parse *parse, t_frame *frame, char *file_name);
void	make_map(t_parse *parse, t_frame *frame);

//Check_map
int		check_elements_on_top(t_parse *parse);
int		check_elementes(t_parse *parse, int i, int j);
int		check_borders(t_parse *parse, t_frame *frame);

//Reas textures
char	*get_texture(t_parse *parse, int i, int j, int skip_name);
void	read_textures(t_parse *parse);

//Parse_utils
int		check_newline_map(char *str);
void	get_position(t_parse *parse, t_frame *frame, int i, int j);
int		check_valid_characters_map(t_parse *parse);
// int		check_spaces(t_parse *parse);

//Movement
void	move_player(t_key *key, t_player *pl, char *map);
void	turn_player(t_key *key, t_player *pl);

//Mouse/Key events
int	red_cross(int keycode, t_key *key);
int	key_release(int keycode, t_key *key);
int	key_press(int keycode, t_key *key);
int	check_keys(t_key *key, int type);

#endif
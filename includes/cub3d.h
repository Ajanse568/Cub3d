/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 18:19:14 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/21 11:23:18 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_parse {
	char	*ch;
	char	*str;
	char	**args;
	char	**map;
	int		count_args;
	char	*walls[4];
	char	*floor;
	char	*ceiling;
	int		i;
	int		f_check;
	int		c_check;
}				t_parse;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player {
	float	px;
	float	py;
	float	pa;
	float	pdx;
	float	pdy;
}				t_player;

typedef struct s_key {
	int	w;
	int	a;
	int	s;
	int	d;
	int	c_l;
	int	c_r;
}				t_key;

typedef struct s_map {
	char	*map;
	t_data	walls[4];
	int		floor;
	int		ceiling;
	int		map_width;
	int		map_height;
}			t_map;

typedef struct s_frame {
	void			*mlx;
	void			*mlx_win;
	t_player		*pl;
	t_map			*map_conf;
	t_key			*key;
}					t_frame;

typedef struct s_ray {
	float	fx;
	float	fy;
	float	ya;
	float	xa;
	float	dist;
}				t_ray;

typedef struct s_line {
	int		pos;
	int		width;
	float	ra;
	int		h_or_v;
	t_ray	ray;
}				t_line;

typedef struct s_draw {
	int		dist;
	int		wall_x;
	int		floor;
	int		ceiling;
	t_line	li;
	t_data	*wall;
	t_data	*img;
}				t_draw;

# define ESC					53
# define W						13
# define A						0
# define S						1
# define D						2
# define C_L					123
# define C_R					124
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define SCREEN_WIDTH			960
# define SCREEN_HEIGHT			500

//Raycast
float	fix_ang(float a);
float	deg_to_rad(float a);
void	cast_rays(t_player pl, t_map map_conf, t_data *img);
float	ray_dist(t_player pl, t_ray *ray, float ra, t_map map_conf);

//Draw
void	draw_wall(t_line li, t_data *walls, t_map map_conf, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//Parsing
void	init_parse(t_parse *parse);
void	parsing(t_parse *parse, t_frame *frame, char *file_name);
void	make_map(t_parse *parse, t_frame *frame);
void	floor_ceiling_to_hex(t_parse *parse, t_map *map_conf);

//Check_map
int		check_elements_on_top(t_parse *parse);
int		check_elementes(t_parse *parse, int i, int j);
int		check_borders(t_parse *parse, t_frame *frame);

//Reas textures
char	*get_texture(t_parse *parse, int i, int j, int skip_name);
void	read_textures(t_parse *parse);

//Parse_utils
void	get_height_and_width(t_parse *parse, t_frame *frame);
int		check_newline_map(char *str);
void	get_position(t_parse *parse, t_frame *frame, int i, int j);
int		check_valid_characters_map(t_parse *parse, t_map map_conf);
char	*ft_strjoin_free(char *s1, char const *s2);
void	init_parse(t_parse *parse);
int		arrlen(char **map_d);
int		linelen(char **map_d);

//Movement
void	move_player(t_key *key, t_player *pl, t_map *map_conf);
void	turn_player(t_key *key, t_player *pl);

//Mouse/Key events
int		red_cross(int keycode, t_key *key);
int		key_release(int keycode, t_key *key);
int		key_press(int keycode, t_key *key);
int		check_keys(t_key *key, int type);

//Utils
void	exit_program(char *exit_message);
char	*ft_substr_free(char const *s, unsigned int start, unsigned int len);
void	*protect(void *alloc);

#endif
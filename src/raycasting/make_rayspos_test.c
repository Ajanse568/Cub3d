/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_rayspos_test.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 14:13:14 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/04 11:09:30 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_ray	verticast(float ra, t_player pl, float Tan)
{
	t_ray	ray;

	if (cos(deg_to_rad(ra)) > 0.001)
	{
		ray.fx = (((int)pl.px >> 6) << 6) + 64;
		ray.fy = pl.py + ((pl.px - ray.fx) * Tan);
		ray.xa = 64;
		ray.ya = -64 * Tan;
	}
	else if (cos(deg_to_rad(ra)) < -0.001)
	{
		ray.fx = (((int)pl.px >> 6) << 6) - 0.0001;
		ray.fy = pl.py + ((pl.px - ray.fx) * Tan);
		ray.xa = -64;
		ray.ya = 64 * Tan;
	}
	else
	{
		ray.fx = pl.px;
		ray.fy = pl.py;
	}
	return (ray);
}

t_ray	horicast(int ra, t_player pl, float Tan)
{
	t_ray	ray;

	Tan = 1.0 / Tan;
	if (sin(deg_to_rad(ra)) > 0.001)
	{
		ray.fy = (((int)pl.py >> 6) << 6) - 0.0001;
		ray.fx = pl.px + ((pl.py - ray.fy) * Tan);
		ray.ya = -64;
		ray.xa = 64 * Tan;
	}
	else if (sin(deg_to_rad(ra)) < -0.001)
	{
		ray.fy = (((int)pl.py >> 6) << 6) + 64;
		ray.fx = pl.px + ((pl.py - ray.fy) * Tan);
		ray.ya = 64;
		ray.xa = -64 * Tan;
	}
	else
	{
		ray.fx = pl.px;
		ray.fy = pl.py;
	}
	return (ray);
}

void	init_ray(t_line *li, t_player pl, t_map map_conf)
{
	float	mytan;
	t_ray	hor;
	t_ray	vert;

	mytan = tan(deg_to_rad(li->ra));
	hor = horicast(li->ra, pl, mytan);
	vert = verticast(li->ra, pl, mytan);
	hor.dist = ray_dist(pl, &hor, li->ra, map_conf);
	vert.dist = ray_dist(pl, &vert, li->ra, map_conf);
	if (hor.dist < vert.dist)
	{
		li->ray = hor;
		li->h_or_v = 0;
	}
	else
	{
		li->ray = vert;
		li->h_or_v = 1;
	}
}

int	ray_position(float pa, float ra, float fov)
{
	int	rpos;

	rpos = SCREEN_WIDTH / 2 - (0.5f * tan(deg_to_rad(fix_ang(pa - ra))) \
											/ fov) * SCREEN_WIDTH / 2;
	if (rpos < 0)
		rpos *= -1;
	return (rpos);
}

void	cast_rays(t_player pl, t_map map_conf, t_data *img)
{
	int		i;
	float	fov;
	t_line	li;

	i = 0;
	li.ra = fix_ang(pl.pa + 30);
	fov = 0.5f * tan(deg_to_rad(fix_ang(pl.pa - li.ra)));
	while (i < SCREEN_WIDTH)
	{
		init_ray(&li, pl, map_conf);
		li.pos = ray_position(pl.pa, li.ra, fov);
		li.width = ray_position(pl.pa, li.ra - 0.125, fov) - li.pos;
		draw_wall(li, map_conf.walls, map_conf, img);
		i += li.width;
		li.ra = fix_ang(li.ra - 0.125);
	}
}

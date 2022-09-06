#include "cub3d.h"
#include <math.h>
#include <stdio.h>

// float	 calc_dist(t_player pl, t_ray *ray, float ra, t_map map_conf)
// {
//  int	  dof;
//  float   dist;
//  int     mp;

//  dist = 10000;
//  dof = 0;
//  if (ray->fx == pl.px && ray->fy == pl.py)
//      return (dist);
//  while (dof < (map_conf.map_width - 2))
//  {
//      mp = ((int)ray->fx >> 6) + (((int)ray->fy >> 6) * (map_conf.map_width));
//      if (mp > 0 && mp < map_conf.map_width * map_conf.map_height \
//          && map_conf.map[mp] == '1')
//      {
//          dof = map_conf.map_width - 2;
//          dist = cos(degToRad(ra)) * (ray->fx - pl.px) - \
//          sin(degToRad(ra)) * (ray->fy - pl.py);
//      }
//      else
//      {
//          ray->fx += ray->xa;
//          ray->fy += ray->ya;
//          dof++;
//      }
//  }
//  return (dist);
// }

t_ray	verticast(float ra, t_player pl, float Tan)
{
	t_ray	ray;

	if (cos(degToRad(ra)) > 0.001)
	{
		ray.fx = (((int)pl.px >> 6) << 6) + 64;
		ray.fy = pl.py + ((pl.px - ray.fx) * Tan);
		ray.xa = 64;
		ray.ya = -64 * Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
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
	if (sin(degToRad(ra)) > 0.001)
	{
		ray.fy = (((int)pl.py >> 6) << 6) - 0.0001;
		ray.fx = pl.px + ((pl.py - ray.fy) * Tan);
		ray.ya = -64;
		ray.xa = 64 * Tan;
	}
	else if (sin(degToRad(ra)) < -0.001)
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

void	 init_ray(t_line *li, t_player pl, t_map map_conf)
{
	float	mytan;
	t_ray	hor;
	t_ray	vert;

	mytan = tan(degToRad(li->ra));
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

int ray_position(float pa, float ra, float fov)
{
	int rpos;

	rpos = SCREEN_WIDTH / 2 - (0.5f * tan(degToRad(FixAng(pa - ra))) / fov) * SCREEN_WIDTH / 2;
	if (rpos < 0)
		rpos *= -1;
	return (rpos);
}

void	 cast_rays(t_player pl, t_map map_conf, t_data *img)
{
	int		i;
	float	fov;
	t_line	li;

	i = 0;
	li.ra = FixAng(pl.pa + 30);
	fov = 0.5f * tan(degToRad(FixAng(pl.pa - li.ra)));
	while (i < SCREEN_WIDTH)
	{
		//printf("%i:%f\n", i, SCREEN_WIDTH / 2 - (0.5f * tan(degToRad(FixAng(pl.pa - li.ra))) / fov) * SCREEN_WIDTH / 2);
		init_ray(&li, pl, map_conf);
		li.pos = ray_position(pl.pa, li.ra, fov);
		li.width = ray_position(pl.pa, li.ra - 0.125, fov) - li.pos;
		draw_wall(li, map_conf.walls, img);
		i += li.width;
		li.ra = FixAng(li.ra - 0.125);
	}
}
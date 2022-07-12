/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/12 17:50:40 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

// float	calc_dist(t_player pl, t_ray *ray, float ra, t_map map_conf)
// {
// 	int		dof;
// 	float	dist;
// 	int		mp;

// 	dist = 10000;
// 	dof = 0;
// 	if (ray->fx == pl.px && ray->fy == pl.py)
// 		return (dist);
// 	while (dof < (map_conf.map_width - 2))
// 	{
// 		mp = ((int)ray->fx >> 6) + (((int)ray->fy >> 6) * (map_conf.map_width));
// 		if (mp > 0 && mp < map_conf.map_width * map_conf.map_height \
// 			&& map_conf.map[mp] == '1')
// 		{
// 			dof = map_conf.map_width - 2;
// 			dist = cos(degToRad(ra)) * (ray->fx - pl.px) - \
// 			sin(degToRad(ra)) * (ray->fy - pl.py);
// 		}
// 		else
// 		{
// 			ray->fx += ray->xa;
// 			ray->fy += ray->ya;
// 			dof++;
// 		}
// 	}
// 	return (dist);
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

void	cast_rays(t_player pl, t_map map_conf, t_data *img)
{
	float	mytan;
	t_ray	hor;
	t_ray	vert;
	float	ra;
	int		i;
	float	fov;

	i = 0;
	ra = FixAng(pl.pa + 30);
	fov = 0.5f * tan(degToRad(FixAng(pl.pa - ra)));
	printf("fov:%f\n", fov);
	while (i < 960)
	{
		printf("%i:%f\n", i, 480 - (0.5f * tan(degToRad(FixAng(pl.pa - ra))) / fov) * 480);
		mytan = tan(degToRad(ra));
		hor = horicast(ra, pl, mytan);
		vert = verticast(ra, pl, mytan);
		hor.dist = ray_dist(pl, &hor, ra, map_conf);
		vert.dist = ray_dist(pl, &vert, ra, map_conf);
		if (hor.dist < vert.dist)
			draw_wall(hor, i, map_conf.walls, img);
		else
			draw_wall(vert, i, map_conf.walls, img);
		i += 2;
		ra = FixAng(ra - 0.125);
	}
}

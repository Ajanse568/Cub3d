/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/05 15:08:57 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define MapW 16

float	calc_dist(t_player pl, t_ray *ray, float ra, char *map)//, t_data *img)
{
	int		dof;
	float	dist;
	int		mp;

	dist = 10000;
	dof = 0;
	if (ray->fx == pl.px && ray->fy == pl.py)
		dof = MapW - 2;
	while (dof < (MapW - 2))
	{
		mp = ((int)ray->fx>>6) + (((int)ray->fy>>6) * 8);
		if (mp > 0 && mp < 16 * 8 && map[mp] == 49)
		{
			dof = MapW - 2;
			dist = cos(degToRad(ra)) * (ray->fx - pl.px) - \
			sin(degToRad(ra)) * (ray->fy - pl.py);
		}
		else
		{
			ray->fx += ray->xa;
			ray->fy += ray->ya;
			dof++;
		}
	}
	return (dist);
}

t_ray	verticast(float ra, t_player pl, float Tan)
{
	t_ray	ray;

	if (cos(degToRad(ra)) > 0.001)
	{
		ray.fx = (((int)pl.px>>6)<<6) + 64;
		ray.fy = pl.py + ((pl.px - ray.fx) * Tan);
		ray.xa = 64;
		ray.ya = -64 * Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		ray.fx = (((int)pl.px>>6)<<6) - 0.0001;
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
		ray.fy = (((int)pl.py>>6)<<6) - 0.0001;
		ray.fx = pl.px + ((pl.py - ray.fy) * Tan);
		ray.ya = -64;
		ray.xa = 64 * Tan;
	}
	else if (sin(degToRad(ra)) < -0.001)
	{
		ray.fy = (((int)pl.py>>6)<<6) + 64;
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

void	raycast(t_player pl, char *map, t_data *img, t_data wall)
{
	float	Tan;
	t_ray	hor;
	t_ray	vert;
	float	ra;
	int		i = 0;

	ra = FixAng(pl.pa + 30);
	while (i < 320 * 3)
	{
		Tan = tan(degToRad(ra));
		hor = horicast(ra, pl, Tan);
		vert = verticast(ra, pl, Tan);
		hor.dist = calc_dist(pl, &hor, ra, map);//, img);
		vert.dist = calc_dist(pl, &vert, ra, map);//, img);
		vert.dist = vert.dist * cos(degToRad(FixAng(pl.pa - ra)));
		hor.dist = hor.dist * cos(degToRad(FixAng(pl.pa - ra)));
		if (hor.dist < vert.dist)
		{
			//draw_circle(img, hor.fx, hor.fy, 2);
			draw_line(hor.dist, (int)hor.fx % 64, i, &wall, img);
		}
		else
		{
			//draw_circle(img, vert.fx, vert.fy, 2);
			draw_line(vert.dist, (int)vert.fy % 64, i, &wall, img);
		}
		i++;
		ra = FixAng(ra - 0.1875 / 3);//0.25 / 2);
	}
}

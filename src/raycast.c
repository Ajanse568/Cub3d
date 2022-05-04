/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/05/04 15:22:35 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define MapW 16

float	calc_dist(t_player pl, t_ray *ray, float ra, int *map)//, t_data *img)
{
	int		dof;
	float	dist;
	int		mp;

	dist = 10000;
	dof = 0;
	if(ray->fx == pl.px && ray->fy == pl.py)
		dof = MapW - 2;
	while(dof < (MapW - 2))
	{
		mp = (int)ray->fx / 100 + ((int)ray->fy / 100 * 8);
		//printf("mp: %i\n", mp);
		if (mp > 0 && mp < 16*8 && map[mp] == 1)
		{
			dof = MapW - 2;
			dist = cos(degToRad(ra))*(ray->fx-pl.px)-sin(degToRad(ra))*(ray->fy-pl.py);
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
		ray.fx = (int)(pl.px/100) * 100 + 100;
		ray.fy = pl.py + ((pl.px - ray.fx)*Tan);
		ray.xa = 100;
		ray.ya = -100*Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		ray.fx = (int)(pl.px/100) * 100 - 0.0001;
		ray.fy = pl.py + ((pl.px - ray.fx)*Tan);
		ray.xa = -100;
		ray.ya = 100*Tan;
	}
	else
	{
		ray.fx = pl.px;
		ray.fy = pl.py;
	}
	return(ray);
}

t_ray	horicast(int ra, t_player pl, float Tan)
{
	t_ray	ray;

	Tan = 1.0/Tan;
	if (sin(degToRad(ra)) > 0.001)
	{
		ray.fy = (int)(pl.py/100) * 100 - 0.0001;
		ray.fx = pl.px + ((pl.py - ray.fy)*Tan);
		ray.ya = -100;
		ray.xa = 100*Tan;
	}
	else if (sin(degToRad(ra)) < -0.001)
	{
		ray.fy = (int)(pl.py/100) * 100 + 100;
		ray.fx = pl.px + ((pl.py - ray.fy)*Tan);
		ray.ya = 100;
		ray.xa = -100*Tan;
	}
	else
	{
		ray.fx = pl.px;
		ray.fy = pl.py;
	}
	return(ray);
}

void	raycast(t_player pl, int *map, t_data *img)
{
	float	Tan;
	t_ray	hor;
	t_ray	vert;
	float	ra;
	int		i = 0;

	ra = FixAng(pl.pa + 30);
	// printf("ra:%f\n", ra);
	while (i < 120 * 2 * 2)
	{
		Tan = tan(degToRad(ra));
		hor = horicast(ra, pl, Tan);
		//printf("hor.fx: %f hor.fy: %f hor.xa: %f hor.ya: %f\n", hor.fx, hor.fy, hor.xa, hor.ya);
		vert = verticast(ra, pl, Tan);
		hor.dist = calc_dist(pl, &hor, ra, map);//, img);
		vert.dist = calc_dist(pl, &vert, ra, map);//, img);
		// if (i%2 == 0)
		// 	printf("line %i\nBefore fish_fix - vert.dist: %f hor.dist: %f\n", i, vert.dist, hor.dist);
		vert.dist = vert.dist*cos(degToRad(FixAng(pl.pa - ra)));
		hor.dist = hor.dist*cos(degToRad(FixAng(pl.pa - ra)));
		// if (i%2 == 0)
		// 	printf("After fish_fix - vert.dist: %f hor.dist: %f\n\n", vert.dist, hor.dist);
		if (hor.dist < vert.dist)
		{
			//draw_circle(img, hor.fx, hor.fy, 2);
			draw_line(hor.dist, 0x008B4513, i, img);
		}
		else
		{
			//draw_circle(img, vert.fx, vert.fy, 2);
			draw_line(vert.dist, 0x00774513, i, img);
		}
		i++;
		ra = FixAng(ra - 0.5 / 2 / 2);
	}
}
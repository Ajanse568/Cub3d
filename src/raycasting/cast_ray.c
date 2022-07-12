/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:50:47 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/12 15:49:05 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	highest(int width, int height)
{
	if (width > height)
		return (width);
	return (height);
}

float	calc_dist(float ra, t_player pl, t_ray *ray)
{
	float	fisheye;
	float	dist;

	fisheye = cos(degToRad(FixAng(pl.pa - ra)));
	dist = cos(degToRad(ra)) * (ray->fx - pl.px) - \
			sin(degToRad(ra)) * (ray->fy - pl.py);
	dist = dist * fisheye;
	return (dist);
}

float	ray_dist(t_player pl, t_ray *ray, float ra, t_map map_conf)
{
	int		dof;
	int		mp;

	dof = 0;
	if (ray->fx == pl.px && ray->fy == pl.py)
		return (10000);
	while (dof < (highest(map_conf.map_width, map_conf.map_height) - 2))
	{
		mp = ((int)ray->fx >> 6) + (((int)ray->fy >> 6) * (map_conf.map_width));
		if (mp > 0 && mp < map_conf.map_width * map_conf.map_height \
										&& map_conf.map[mp] == '1')
			return (calc_dist(ra, pl, ray));
		else
		{
			ray->fx += ray->xa;
			ray->fy += ray->ya;
			dof++;
		}
	}
	return (10000);
}

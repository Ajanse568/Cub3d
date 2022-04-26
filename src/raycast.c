/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/26 09:40:42 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	calc_dist(t_player pl, t_ray ray, int ra, int *map)
{
	int		hit;
	int		dist;

	hit = 0;
	if (map[(ray.fy/100 - 1) * 8 + ray.fx/100])
		hit++;
	while (!hit)
	{
		ray.fy -= ray.ya;
		ray.fx += ray.xa;
		if (map[(ray.fy/100 - 1) * 8 + ray.fx/100])
			hit++;
	}
	dist = (pl.py - ray.fy)/sin(degToRad(ra));
	return(dist * cos(degToRad(ra - pl.pa)));
}

void	horicast(t_player pl, t_ray *ray, float Tan)
{
	ray->fy = (int)(pl.py/100) * 100;
	ray->fx = pl.px + ((pl.py - ray->fy)/Tan);
	ray->ya = 100;
	ray->xa = 100/Tan;
}

void	verticast(t_player pl, t_ray *ray, float Tan)
{
	ray->fx = (int)(pl.py/100) * 100 + 100;
	ray->fy = pl.py + ((pl.px - ray->fx)/Tan);
	ray->xa = 100;
	ray->ya = 100 * Tan;
}

int	raycast(t_player pl, int *map)
{
	float	Tan;
	t_ray	ray;
	int		hor;
	int		vert;
	
	Tan = tan(degToRad(pl.pa));
	horicast(pl, &ray, Tan);
	hor = calc_dist(pl, ray, pl,pa, map);
	verticast(pl, &ray, Tan);
	vert = calc_dist(pl, ray, pl.pa, map);
	if (vert < hor)
		return (vert);
	return (hor);
}
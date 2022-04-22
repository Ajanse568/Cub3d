/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/22 18:08:21 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	calc_dist(t_player pl, t_ray ray, int ra)
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
	return(dist * cos(degToRad(abs(ra - pl.pa))));
}

void	horicast(t_player pl, t_ray *ray, float Tan)
{
	ray->fy = (int)(pl.py/100) * 100;
	ray->fx = pl.px + ((pl.py - ray->fy)/Tan);
	ray->ya = 100;
	ray->xa = 100/Tan;
}

void	vertricast(t_player pl, t_ray *ray, float Tan)
{
	ray->fx = (int)(pl.py/100) * 100 + 100;
	ray->fy = pl.py + ((pl.px - ray->fx)/Tan);
	ray->xa = 100;
	ray->ya = 100 * Tan;
}

void raycast(t_player pl)
{
	float	Tan;
	t_ray	ray;
	int		hor;
	int		vert;
	
	Tan = tan(degToRad(pl.pa));
	horicast(pl, &ray, Tan);
	hor = calc_dist(pl, ray, pl.pa);
	verticast(pl, &ray, Tan);
	vert = calc_dist(pl, ray, pl.pa);
	if (vert < hor)
		return (vert);
	return (hor);
}
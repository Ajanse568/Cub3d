/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:39:56 by ajanse        #+#    #+#                 */
/*   Updated: 2022/05/02 18:08:04 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int	calc_dist(t_player pl, t_ray ray, int ra, int *map, t_data *img)
{
	int		hit;
	int		dist;

	hit = 0;
	//printf("Begin fy: %i fx: %i ya: %f xa: %f\n", (int)ray.fy, (int)ray.fx, ray.ya, ray.xa);
	if (map[((int)ray.fy/100) * 8 + (int)ray.fx/100])
		hit++;
	while (!hit)
	{
		ray.fy -= ray.ya;
		ray.fx += ray.xa;
		if (map[((int)ray.fy/100) * 8 +(int)ray.fx/100])
			hit++;
	}
	//printf("Hit! fy: %i fx: %i ya: %f yx: %f\n", (int)ray.fy, (int)ray.fx, ray.ya, ray.xa);
	if (ray.fx < 800)
		draw_circle(img, ray.fx, ray.fy, 2);
	dist = (pl.py - ray.fy)/sin(degToRad(ra));
	return (dist * cos(degToRad(FixAng(ra - pl.pa))));
}

void	horicast(t_player pl, t_ray *ray, float Tan)
{
	ray->fy = (int)(pl.py/100) * 100 - 1;
	ray->fx = pl.px + ((pl.py - ray->fy)/Tan);
	ray->ya = 100;
	ray->xa = 100/Tan;
	//printf("HOR fy: %f, fx: %f, ya: %f, xa: %f pl.px: %f pl.py: %d result: %f\n", ray->fy, ray->fx, ray->ya, ray->xa, pl.px, (int)pl.py, ((int)pl.py - ray->fy));
}

void	verticast(t_player pl, t_ray *ray, float Tan)
{
	ray->fx = (int)(pl.py/100) * 100 + 100;
	ray->fy = pl.py + ((pl.px - ray->fx)*Tan);
	ray->xa = 100;
	ray->ya = 100 * Tan;
	printf("VERT fy: %f, fx: %f, ya: %f, xa: %f\n", ray->fy, ray->fx, ray->ya, ray->xa);
}

void	raycast(t_player pl, int *map, t_data *img)
{
	float	Tan;
	t_ray	ray;
	int		hor;
	int		vert;
	int		ra;
	int		i = 0;

	ra = FixAng(pl.pa + 30);
	while (i < 60)
	{
		Tan = tan(degToRad(ra));
		printf("ra: %i\n", ra);
		horicast(pl, &ray, Tan);
		// 	draw_circle(img, ray.fx, ray.fy, 2);
		//my_mlx_pixel_put(img, ray.fx, ray.fy, 0x0000FF00);
		if (ray.fx < 800)
			hor = calc_dist(pl, ray, ra, map, img);
		else
			hor = 10000;
		verticast(pl, &ray, Tan);
		// draw_circle(img, ray.fx, ray.fy, 2);
		//my_mlx_pixel_put(img, ray.fx, ray.fy, 0x0000FF00);
		if (ray.fy > 0)
			vert = calc_dist(pl, ray, ra, map, img);
		else 
			vert = 10000;
		if (vert < hor)
			draw_line(vert, 0x00FF0000, i, img);
		else
			draw_line(hor, 0x00330000, i, img);
		i++;
		ra = FixAng(ra - 1);
	}
}
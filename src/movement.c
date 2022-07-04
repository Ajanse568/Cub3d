/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 14:53:01 by ajanse        #+#    #+#                 */
/*   Updated: 2022/05/10 18:11:37 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"

int	check_square(int sign, int sign2, t_player *pl, int *map)
{
	int	n_x;
	int	n_y;

	n_x = pl->px + sign * pl->pdx * 15;
	n_y = pl->py + sign2 * pl->pdy * 15;
	if (map[(n_x>>6) + (n_y>>6) * 8])
		return (0);
	return (1);
}

void	move_player(t_key *key, t_player *pl, int *map)
{
	int	pm;
	int	pm2;

	pm = 1;
	pm2 = 1;
	if (key->s || key->d)
		pm = -1;
	if (key->a || key->s)
		pm2 = -1;
	if ((key->w || key->s) && check_square(pm, pm2, pl, map))
	{
		pl->px += pm * pl->pdx * 5;
		pl->py += pm2 * pl->pdy * 5;
	}
	if (key->a || key->d)
	{
		pl->px += pm * pl->pdy * 3;
		pl->py += pm2 * pl->pdx * 3;
	}
}

void	turn_player(t_key *key, t_player *pl)
{
	int	pm;

	pm = 1;
	if (key->c_r)
		pm = -1;
	if (key->c_l || key->c_r)
	{
		pl->pa += 2 * pm;
		pl->pa = FixAng(pl->pa);
		pl->pdx = cos(degToRad(pl->pa));
		pl->pdy = -sin(degToRad(pl->pa));
	}
}
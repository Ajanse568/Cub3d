/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 14:49:44 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/04 11:05:36 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	check_keys(t_key *key, int type)
{
	if (type == W)
	{
		if (key->w || key->a || key->s || key->d)
			return (0);
	}
	else
	{
		if (key->c_l || key->c_r)
			return (0);
	}
	return (1);
}

int	key_press(int keycode, t_key *key)
{
	if (keycode == W && check_keys(key, W))
		key->w = 1;
	if (keycode == A && check_keys(key, W))
		key->a = 1;
	if (keycode == S && check_keys(key, W))
		key->s = 1;
	if (keycode == D && check_keys(key, W))
		key->d = 1;
	if (keycode == C_L && check_keys(key, C_L))
		key->c_l = C_L;
	if (keycode == C_R && check_keys(key, C_L))
		key->c_r = C_R;
	if (keycode == ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_key *key)
{
	if (keycode == W)
		key->w = 0;
	if (keycode == A)
		key->a = 0;
	if (keycode == S)
		key->s = 0;
	if (keycode == D)
		key->d = 0;
	if (keycode == C_L)
		key->c_l = 0;
	if (keycode == C_R)
		key->c_r = 0;
	return (0);
}

int	red_cross(int keycode, t_key *key)
{
	(void)keycode;
	(void)key;
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 15:20:51 by ajanse        #+#    #+#                 */
/*   Updated: 2022/04/22 15:21:20 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float degToRad(int a) 
{ 
	return a * M_PI / 180.0;
}

int FixAng(int a)
{
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return a;
}

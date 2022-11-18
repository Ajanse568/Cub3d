/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 15:20:51 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/15 13:59:13 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include <stdio.h>
#include "libft.h"

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void	exit_program(char *exit_message)
{
	printf("Error\n%s", exit_message);
	exit (1);
}

char	*ft_substr_free(char const *s, unsigned int start, unsigned int len)
{
	char			*dst;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (protect(ft_strdup("\0")));
	if ((unsigned)ft_strlen(s + start) < len)
		dst = protect(malloc(sizeof(char) * (ft_strlen(s + start) + 1)));
	else
		dst = protect(malloc(sizeof(char) * (len + 1)));
	while (i < len && (s + start)[i])
	{
		dst[i] = (s + start)[i];
		i++;
	}
	dst[i] = 0;
	free((void *)s);
	return (dst);
}

void	*protect(void *alloc)
{
	if (!alloc)
		exit_program("Malloc");
	return (alloc);
}

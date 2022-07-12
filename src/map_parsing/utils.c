/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 15:20:51 by ajanse        #+#    #+#                 */
/*   Updated: 2022/07/12 13:10:28 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

float degToRad(float a) 
{ 
	return a * M_PI / 180.0;
}

float FixAng(float a)
{
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return a;
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
		return (ft_strdup("\0"));
	if ((unsigned)ft_strlen(s + start) < len)
		dst = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (0);
	while (i < len && (s + start)[i])
	{
		dst[i] = (s + start)[i];
		i++;
	}
	dst[i] = 0;
	free((void *)s);
	return (dst);
}

void	get_height_and_width(t_parse *parse, t_frame *frame)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (parse->map[i])
	{
		if ((int)ft_strlen(parse->map[i]) > width)
			width = ft_strlen(parse->map[i]);
		i++;
	}
	frame->map_conf->map_width = width + 1;
	frame->map_conf->map_height = i;
	i = 0;
}
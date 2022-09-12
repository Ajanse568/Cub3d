/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:12:03 by ajanse        #+#    #+#                 */
/*   Updated: 2022/09/12 14:38:49 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char			*dst;
	unsigned int	dsize;

	if (!s1 || !s2)
		return (0);
	dsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = ft_calloc(dsize, sizeof(char));
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s1, dsize);
	ft_strlcat(dst, s2, dsize);
	free(s1);
	return (dst);
}

void	init_parse(t_parse *parse)
{
	parse->count_args = 0;
	parse->ch = ft_calloc(2, 1);
}

int	arrlen(char **map_d)
{
	int	i;

	i = 0;
	while (map_d[i])
		i++;
	return (i);
}

int	linelen(char **map_d)
{
	int	longest;
	int	len;
	int	i;

	i = 0;
	longest = 0;
	while (map_d[i])
	{
		len = ft_strlen(map_d[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest + 1);
}

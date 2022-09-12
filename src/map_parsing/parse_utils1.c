#include "cub3d.h"
#include "libft.h"

void	init_parse(t_parse *parse)
{
	parse->count_args = 0;
	parse->ch = ft_calloc(2, 1);
	parse->str = ft_calloc(2, 1);
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

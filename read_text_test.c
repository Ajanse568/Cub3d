/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_text_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 14:34:41 by ajanse        #+#    #+#                 */
/*   Updated: 2022/11/02 14:38:19 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	read_textures(t_parse *parse)
{
	char	*wind = "NOSOWEEA";
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (parse->args[j])
		{
			if (!ft_strncmp(wind + i * 2, parse->args[j], 2))
			{
				parse->walls[i] = get_texture(parse, j, j, 2);
				break ;
			}
			j++;
		}
		if (!parse->args[j])
			exit_program("Missing argument!");
		i++;
	}
	if (parse->count_args != 6)
		exit_program("Missing argument!");
	parse->i = i;
}
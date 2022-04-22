/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:11:32 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/08 17:17:39 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_buff(char *tmp, int index)
{
	while (index >= 0)
	{
		tmp[index] = 0;
		index--;
	}
}

void	ft_strncpy(char *dst, char *str, int len)
{
	int	i;

	i = 0;
	if (dst && str)
	{
		while (i < len)
		{
			dst[i] = str[i];
			i++;
		}
		if (dst[i - 1])
			dst[i] = 0;
	}
}

int	shift_buff(char *tmp, int index)
{
	if (tmp[index] == '\n')
	{
		ft_strncpy(tmp, tmp + index + 1, ft_strlen(&tmp[index + 1]) + 1);
		return (1);
	}
	return (0);
}

int	newl_end_search(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return (-1);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	return (i);
}

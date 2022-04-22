/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:41:24 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/03 18:41:25 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *str, unsigned int dsize)
{
	int	l;

	l = ft_strlen(str);
	if (!dsize)
		return (l);
	while (dsize > 1 && *str)
	{
		*dst = *str;
		dst++;
		str++;
		dsize--;
	}
	*dst = '\0';
	return (l);
}

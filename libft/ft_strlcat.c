/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:41:20 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/03 18:41:22 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *str, unsigned int dsize)
{
	unsigned int	l;

	l = ft_strlen(dst);
	if (dsize > l)
		ft_strlcpy(dst + l, str, dsize - l);
	else
		return (ft_strlen(str) + dsize);
	l += ft_strlen(str);
	return (l);
}

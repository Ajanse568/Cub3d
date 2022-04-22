/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:40:32 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/16 14:59:38 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *str, size_t len)
{
	unsigned char	*ptr;
	const char		*ptr2;

	ptr = dst;
	ptr2 = (const char *)str;
	if (!dst && !str)
		return (0);
	while (len > 0)
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
		len--;
	}
	return (dst);
}

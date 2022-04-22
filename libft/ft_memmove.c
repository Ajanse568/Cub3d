/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:40:36 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/03 18:40:37 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *str, size_t len)
{
	unsigned int	i;
	unsigned char	*ptr;
	const char		*ptr2;

	i = len;
	ptr = dst;
	ptr2 = (const char *)str;
	if (!dst && !str)
		return (0);
	if (str + len >= dst && str < dst)
	{
		while (i-- > 0)
			ptr[i] = ptr2[i];
	}
	else
		ft_memcpy(dst, str, len);
	return (dst);
}

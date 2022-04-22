/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanse <ajanse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:41:07 by ajanse            #+#    #+#             */
/*   Updated: 2021/12/03 18:41:08 by ajanse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	void	*dst;

	len = ft_strlen(s1) + 1;
	dst = malloc(len);
	if (!dst)
		return (0);
	return (ft_memcpy(dst, s1, len));
}

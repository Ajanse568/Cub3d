/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/03 18:41:16 by ajanse        #+#    #+#                 */
/*   Updated: 2022/03/15 15:38:05 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (dst);
}

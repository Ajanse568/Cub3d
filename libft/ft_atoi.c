/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/03 18:37:24 by ajanse        #+#    #+#                 */
/*   Updated: 2022/03/14 17:53:18 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	whitespace(const char *s, int c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	tot;
	int		mp;

	tot = 0;
	mp = 0;
	while (whitespace(" \n\t\v\r\f", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		mp = *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tot = tot * 10 + (*str - 48);
		str++;
	}
	if (mp == '-')
		return (tot * -1);
	return (tot);
}

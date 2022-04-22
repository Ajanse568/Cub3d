/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_ptrarray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajanse <ajanse@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 18:10:00 by ajanse        #+#    #+#                 */
/*   Updated: 2022/02/15 18:10:05 by ajanse        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_ptrarray(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:18:03 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/19 13:31:32 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/types.h>
#include <unistd.h>

void	ft_free_list(char **path_list)
{
	int	index;

	index = 0;
	while (path_list[index])
	{
		free(path_list[index]);
		index++;
	}
	free(path_list);
}

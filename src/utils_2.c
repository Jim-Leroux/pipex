/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:03:31 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/19 16:28:59 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	go_pipex(t_args *args_list, char **envp)
{
	t_args	*head;

	head = args_list;
	while (args_list)
	{
		if (pipex_logic(args_list, envp) == -1)
			return (0);
		if (args_list->here_doc == 1 && args_list->next)
			args_list->next->here_doc = 1;
		args_list = args_list->next;
	}
	args_list = head;
	while (head)
	{
		waitpid(head->pid, NULL, 0);
		head = head->next;
	}
	return (1);
}

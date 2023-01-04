/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:03:31 by jileroux          #+#    #+#             */
/*   Updated: 2023/01/03 16:24:55 by jileroux         ###   ########.fr       */
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

int	def_pipe(t_args *args_list)
{
	if (args_list->redir_type == IN)
	{
		args_list->fds[IN] = open(args_list->file, O_RDONLY);
		if (args_list->fds[IN] < 0)
			return (0);
	}
	else if (args_list->redir_type == OUT)
	{
		if (args_list->here_doc == 1)
			args_list->fds[OUT] = open(args_list->file, O_WRONLY
					| O_APPEND, 0644);
		else
			args_list->fds[OUT] = open(args_list->file, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (args_list->fds[OUT] < 0)
			return (0);
	}
	return (1);
}

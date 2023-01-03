/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:21:34 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/19 16:26:25 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_args	*lst_new(void *content, char **envp)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (arg == NULL)
		return (NULL);
	arg->cmd = content;
	arg->envp = envp;
	arg->fds[0] = 0;
	arg->fds[1] = 0;
	arg->file = NULL;
	arg->here_doc = 0;
	arg->options = NULL;
	arg->pid = -1;
	arg->redir_type = DEFAULT;
	arg->next = NULL;
	return (arg);
}

t_args	*ft_lstadd_back(t_args **lst, t_args *new)
{
	t_args	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	return (*lst);
}

t_args	*ft_lstlast(t_args *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	free_list(t_args *args_list)
{
	t_args	*tmp;

	while (args_list)
	{
		tmp = args_list;
		args_list = args_list->next;
		free(tmp);
	}
}

void	print_list(t_args *args_list)
{
	while (args_list)
	{
		args_list = args_list->next;
	}
}

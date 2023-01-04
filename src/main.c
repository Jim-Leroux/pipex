/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:55:54 by jileroux          #+#    #+#             */
/*   Updated: 2023/01/03 16:25:35 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*args_list;
	t_args	*head;

	if (parsing(argc, argv, envp) == 0)
		return (0);
	stack_args(argc, ++argv, envp, &args_list);
	head = args_list;
	if (ft_strcmp(argv[0], "here_doc") == 0)
	{
		here_doc_logic(argv);
		args_list = args_list->next;
		args_list->here_doc = 1;
		free(head);
		args_list->file = ".temp_file_tmp";
	}
	args_list->redir_type = IN;
	if (go_pipex(args_list, envp) == 0)
	{
		free_list(args_list);
		return (perror("Error"), EXIT_FAILURE);
	}
	free_list(args_list);
	unlink("./.temp_file_tmp");
	return (EXIT_SUCCESS);
}

int	stack_args(int argc, char **argv, char **envp, t_args **args_list)
{
	int		index;
	t_args	*tmp;

	index = 1;
	(*args_list) = lst_new(argv[index++], envp);
	tmp = *args_list;
	(*args_list)->file = argv[0];
	while (index < argc - 2)
	{
		tmp = lst_new(argv[index], envp);
		ft_lstadd_back(args_list, tmp);
		tmp = tmp->next;
		index++;
	}
	tmp = *args_list;
	while (tmp)
	{
		if ((tmp)->next == NULL)
			(tmp)->file = argv[argc - 2];
		(tmp) = (tmp)->next;
	}
	return (1);
}

int	pipex_logic(t_args *args_list, char **envp)
{
	char	*tmp;

	args_list->options = ft_split(args_list->cmd, ' ');
	tmp = args_list->options[0];
	args_list->options[0] = ft_get_path(envp, tmp);
	free(tmp);
	if (!args_list->next)
		args_list->redir_type = OUT;
	if (define_pipe(args_list) == 0)
	{
		ft_free_list(args_list->options);
		return (0);
	}
	args_list->pid = fork();
	if (args_list->pid == 0)
		dup_and_exec(args_list, envp);
	close(args_list->fds[IN]);
	close(args_list->fds[OUT]);
	ft_free_list(args_list->options);
	return (0);
}

int	define_pipe(t_args *args_list)
{
	int	pipe_fd[MAX_FD];

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	if (def_pipe(args_list) == 0)
		return (0);
	if (args_list->next)
	{
		pipe(pipe_fd);
		args_list->fds[OUT] = pipe_fd[OUT];
		args_list->next->fds[IN] = pipe_fd[IN];
	}
	return (1);
}

int	dup_and_exec(t_args *args_list, char **envp)
{
	int	dup_in;
	int	dup_out;

	dup_in = dup2(args_list->fds[IN], STDIN_FILENO);
	close(args_list->fds[IN]);
	dup_out = dup2(args_list->fds[OUT], STDOUT_FILENO);
	close(args_list->fds[OUT]);
	if (args_list->next && args_list->next->fds[IN] != STDIN_FILENO)
		close(args_list->next->fds[IN]);
	execve(args_list->options[0], args_list->options, envp);
	ft_free_list(args_list->options);
	return (0);
}

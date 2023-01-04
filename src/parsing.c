/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:09:38 by jileroux          #+#    #+#             */
/*   Updated: 2023/01/04 17:13:48 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parsing(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (write(2, "Error: Wrong arguments\n", 23), 0);
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
		return (write(2, "Error: Wrong here_doc arguments\n", 32), 0);
	else if (ft_strcmp(argv[1], "here_doc") == 0 && argc >= 6)
		return (1);
	if (parsing_file(argc, argv) == 0 || parsing_cmd(argc, argv, envp) == 0)
		return (0);
	return (1);
}

int	parsing_file(int argc, char **argv)
{
	int		fd[MAX_FD];

	fd[0] = open(argv[1], O_RDWR);
	if (fd[0] == -1)
	{
		if (ft_strcmp(argv[1], "here_doc"))
		{
			return (write(2, "Error: Bad entry fd\n", 20), 0);
		}
	}
	close(fd[0]);
	fd[1] = open(argv[argc - 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		return (write(2, "Error: Bad exit fd\n", 19), 0);
	}
	close(fd[0]);
	close(fd[1]);
	return (1);
}

int	parsing_cmd(int argc, char **argv, char **envp)
{
	int		i;
	char	*path;

	i = 2;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], "") == 0)
			return (write(2, "Error: Wrong command\n", 21), 0);
		path = ft_get_path(envp, argv[i]);
		if (path != NULL)
			free(path);
		else
			return (write(2, "Error: Wrong command\n", 21), 0);
		i++;
	}
	return (1);
}
